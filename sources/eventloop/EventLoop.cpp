/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/08 15:18:27 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"
#include "CGIExecuter.hpp"
#include "Signals.hpp"
#include "CgiExec.hpp"

EventLoop::EventLoop(void): AMessengerClient(NULL) {}

EventLoop::~EventLoop(void)
{
	_cleanUpMap(_handlers.begin(), _handlers.end());
	_cleanUpMap(_eventMap.begin(), _eventMap.end());
}

void EventLoop::registerEventHandler(IEventHandler *eventHandler)
{
	EventType type;
	
	type = eventHandler->getHandleType();
	_handlers.insert(std::make_pair(type, eventHandler));
}

void EventLoop::unregisterEventHandler(IEventHandler *eventHandler)
{
	_handlers.erase(eventHandler->getHandleType());
}

void EventLoop::handleEvents(void)
{
	Event	*event;
	int		fd;

	while (!_eventQueue.empty())
	{
		fd = _getNextEventFromQueue();
		event = _getEventFromMap(_eventMap, fd);
		if (event)
			_handleEvent(event);
		if (event && event->isClientDisconnect())
 			_handleClientDisconnect(event);
		else if (event && event->isFinished())
			_finalizeEvent(event);
		else if (event && event->getActualState() == TYPE_TRANSITION)
			_addEventToQueue(event->getFd());
	}
	//if (Signals::isChildSignalTriggered())
		_checkIfCgiScriptsFinished();
	//_closeTimeoutEvents();
}

ClientID EventLoop::getId(void)
{
	return (EVENTLOOP_ID);
}

void EventLoop::receiveMessage(Message *msg)
{
	MessageType	type;
	int			fd;

	type = msg->getType();
	fd = msg->getFd();
	if (type == EVENT_READ_TRIGGERED)
		_registerReadEvent(fd);
	else if (type == EVENT_WRITE_TRIGGERED)
		_registerWriteEvent(fd);
}

void EventLoop::_handleEvent(Event *ev)
{
	std::map<EventType, IEventHandler*>::iterator	it;
	EventType										type;

	if (ev)
	{
		type = ev->getActualState();
		it = _handlers.find(type);
		if (it != _handlers.end())
			it->second->handleEvent(ev);
		if (type == TYPE_TRANSITION)
			_sendMessages(ev); // change name
	}
}

void EventLoop::_registerReadEvent(int fd)
{
	Event*		event;
	EventType	type;

	event = _getEventFromMap(_eventMap, fd);
	if (!event)
	{
		event = new Event(fd, READ_SOCKET);
		_addEventToMap(fd, event);
		sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_PAUSE_TIMER));
	}
	else if (event)
	{
		type = event->getActualState();
		if ((type == READ_SOCKET && event->getFd() == fd)
			|| (type == READ_CGI && event->getCgiReadFd() == fd))
			_addEventToQueue(fd);
		else
			_handleClientDisconnect(event);
	}
}

void EventLoop::_registerWriteEvent(int fd)
{
	Event*		event;
	EventType	type;

	event = _getEventFromMap(_eventMap, fd);
	if (!event)
		return ;
	type = event->getActualState();
	if ((type == WRITE_EVENT && fd == event->getFd())
		|| (type == WRITE_CGI && fd == event->getCgiWriteFd()))
		_addEventToQueue(fd);
}

void EventLoop::_addEventToMap(Event *event)
{
	if (!event)
		return ;
	_eventMap.insert(std::make_pair(event->getFd(), event));
}

void EventLoop::_addEventToMap(int fd, Event *event)
{
	if (!event)
		return ;
	_eventMap.insert(std::make_pair(fd, event));
}

void EventLoop::_addEventToQueue(int fd)
{
	_eventQueue.push(fd);
}

Event* EventLoop::_getEventFromMap(std::map<int, Event*> &map, int fd)
{
	std::map<int, Event*>::iterator	it;

	it = map.find(fd);
	if (it != map.end())
		return (it->second);
	return (NULL);
}

void EventLoop::_deleteEvent(int fd)
{
	Event*	event;
	int		cgiReadFd;
	int		cgiWriteFd;

	event = _getEventFromMap(_cgiEventMap, fd);
	if (event)
		_cgiEventMap.erase(fd);
	event = _getEventFromMap(_eventMap, fd);
	if (event)
	{
		cgiReadFd = event->getCgiReadFd();
		cgiWriteFd = event->getCgiWriteFd();
		if (_getEventFromMap(_eventMap, cgiReadFd))
			_eventMap.erase(cgiReadFd);
		if (_getEventFromMap(_eventMap, cgiWriteFd))
			_eventMap.erase(cgiWriteFd);
		_eventMap.erase(fd);
		delete event;
	}
}

// Not used but will be used and changed
void EventLoop::_closeTimeoutEvents(void)
{
	std::map<int, Event*>::iterator	it;
	Event							*event;
	int								fd;
	int								fdCgi;

	if (_eventMap.empty())
		return ;
	for (it = _eventMap.begin(); it != _eventMap.end(); it++)
	{
		event = it->second;
		fd = event->getFd();
		fdCgi = event->getCgiFd();
		if (fdCgi == it->first)
			continue ;
		if (event->isEventTimeout())
		{
			if (fdCgi)
			{
				_eventMap.erase(fdCgi);
				sendMessage(new Message(EVENTDEMUX_ID, fdCgi, EVENT_REMOVE));
			}
			_deleteEvent(fd);
			sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
			sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
		}
	}
}

void EventLoop::_checkIfCgiScriptsFinished(void)
{
	std::map<int, Event*>::iterator	itMap;
	std::map<int, Event*>::iterator	itMapBackUp;
	Event							*event;
	int								fd;

	if (_cgiEventMap.empty())
		return ;
	itMap = _cgiEventMap.begin();
	while (itMap != _cgiEventMap.end())
	{
		fd = itMap->first;
		if (!_getEventFromMap(_eventMap, fd))
		{
			_cgiEventMap.erase(itMap);
			continue ;
		}
		event = itMap->second;

		if (event->isCgiScriptEndend())
		{
			event->setActualState(TYPE_TRANSITION);
			_addEventToQueue(fd);
			itMapBackUp = itMap;
			itMapBackUp++;
			_cgiEventMap.erase(itMap);
			itMap = itMapBackUp;
			continue ;
		}
		else if (CgiExec::isEnded(event))
			event->setCgiScriptEndend(true);
		itMap++;
	}
}

/*
void EventLoop::_checkIfCgiScriptsFinished(void)
{
	std::map<int, Event*>::iterator	itMap;
	std::map<int, Event*>::iterator	itMapBackUp;
	Event							*event;
	int								fd;
	int								status;

	if (_cgiEventMap.empty())
		return ;
	itMap = _cgiEventMap.begin();
	while (itMap != _cgiEventMap.end())
	{
		fd = itMap->first;
		if (!_getEventFromMap(_eventMap, fd))
		{
			_cgiEventMap.erase(itMap);
			continue ;
		}
		event = itMap->second;

		if (event->isCgiScriptEndend())
		{
			event->setActualState(TYPE_TRANSITION);
			_addEventToQueue(fd);
			itMapBackUp = itMap;
			itMapBackUp++;
			_cgiEventMap.erase(itMap);
			itMap = itMapBackUp;
			continue ;
		}
		else if (CgiExec::isEnded(event))
			event->setCgiScriptEndend(true);
		itMap++;
	}
}
*/


/*
void EventLoop::_checkIfCgiScriptsFinished(void)
{
	std::map<int, Event*>::iterator	itMap;
	std::map<int, Event*>::iterator	itMapBackUp;
	Event							*event;
	int								fd;
	int								status;

	if (_cgiEventMap.empty())
		return ;
	itMap = _cgiEventMap.begin();
	while (itMap != _cgiEventMap.end())
	{
		fd = itMap->first;
		if (!_getEventFromMap(_eventMap, fd))
		{
			_cgiEventMap.erase(itMap);
			continue ;
		}
		event = itMap->second;
		status = event->getCgiExitStatus();
		if (status == NO_EXIT_STATUS)
			event->isCgiScriptEnd();
		else if (status != NO_EXIT_STATUS)
		{
			event->setActualState(TYPE_TRANSITION);
			_addEventToQueue(fd);
			itMapBackUp = itMap;
			itMapBackUp++;
			_cgiEventMap.erase(itMap);
			itMap = itMapBackUp;
			continue ;
		}
		itMap++;
	}
}
*/

void EventLoop::_finalizeEvent(Event *event)
{
	int	fd;

	fd = event->getFd();

	//std::cout << "fd que tem de eliminar: " << fd << std::endl;

	//_showEventMap();

	if (event->isConnectionClose())
		_handleClientDisconnect(event);
	else
		_deleteEvent(fd);
	
	//_showEventMap();
}

void EventLoop::_handleClientDisconnect(Event *event)
{
	int			fd;
	int			cgiReadFd;
	int			cgiWriteFd;
	EventType	type;
	
	fd = event->getFd();
	cgiReadFd = event->getCgiReadFd();
	cgiWriteFd = event->getCgiWriteFd();
	type = event->getActualState();
	sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
	sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
	if (cgiReadFd > 0 && type == READ_CGI)
		sendMessage(new Message(EVENTDEMUX_ID, cgiReadFd, EVENT_REMOVE));
	if (cgiWriteFd > 0 && type == WRITE_CGI)
		sendMessage(new Message(EVENTDEMUX_ID, cgiWriteFd, EVENT_REMOVE));
	_deleteEvent(fd);
}

int EventLoop::_getNextEventFromQueue(void)
{
	int fd;

	fd = _eventQueue.front();
	_eventQueue.pop();
	return (fd);
}

// Function to refactoring
void EventLoop::_sendMessages(Event *event)
{
	EventType	type;
	int			fd;
	
	type = event->getActualState(); // getActualType() change name
	fd = event->getFd();
	if (type == WRITE_EVENT)
	{
		if (event->getCgiReadFd() > 0)
			sendMessage(new Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_REMOVE));
		if (event->getCgiWriteFd() > 0)
			sendMessage(new Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_REMOVE));
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_WRITE));

	}
	else if (type == READ_SOCKET)
	{
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_READ));
		sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_RESTART_TIMER));
	}
	else if (type == WRITE_CGI)
	{
		_cgiEventMap.insert(std::make_pair(event->getFd(), event));
		//event->cgiExecute();
		_eventMap.insert(std::make_pair(event->getCgiWriteFd(), event));
		sendMessage(new Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_ADD_NEW));
		sendMessage(new Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_CHANGE_TO_WRITE));
	}
	else if (type == READ_CGI)
	{
		sendMessage(new Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_REMOVE));
		_eventMap.insert(std::make_pair(event->getCgiReadFd(), event));
		sendMessage(new Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_ADD_NEW));
	}
}

template <typename T>
void EventLoop::_cleanUpMap(T begin, T end)
{
	T it;

	for (it = begin; it != end; it++)
		delete it->second;
}

void EventLoop::_showEventMap(void)
{
	std::map<int, Event*>::iterator it;

	std::cout << "show _eventMap" << std::endl;
	for (it = _eventMap.begin(); it != _eventMap.end(); it++)
		std::cout << "fd: " << it->first << std::endl;
	
	//_eventMap.clear();
}

void EventLoop::_showCgiEventMap(void)
{
	std::map<int, Event*>::iterator it;

	std::cout << "show _cgiEventMap" << std::endl;
	for (it = _cgiEventMap.begin(); it != _cgiEventMap.end(); it++)
		std::cout << it->first << std::endl;

	//_cgiEventMap.clear();
}
