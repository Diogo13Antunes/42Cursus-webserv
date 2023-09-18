/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/18 15:26:31 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"
#include "Signals.hpp"
#include "CgiExec.hpp"

EventLoop::EventLoop(void): AMessengerClient(NULL) {}

EventLoop::~EventLoop(void)
{
	_cleanHandlers();
	_cleanEvents();
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

/*
void EventLoop::handleEvents(void)
{
	Event	*event;
	int		fd;

	while (!_eventQueue.empty())
	{
		fd = _getNextEventFromQueue();
		event = _getEventFromMap(_eventMap, fd);exit(0);
		else if (event && event->isFinished())
			_finalizeEvent(event);
		else if (event && event->getActualState() == TYPE_TRANSITION)
			_addEventToQueue(event->getFd());
	}
	_checkIfCgiScriptsFinished();
	_closeTimeoutEvents();
}
*/

void EventLoop::handleEvents(void)
{
	Event	*event;
	int		fd;

	while (!_eventQueue.empty())
	{
		fd = _getNextEventFromQueue();
		event = _getEventFromMap(_eventMap, fd);
		if (event)
		{
			_handleEvent(event);
			_changeEventStatus(event);
		}
	}
}

ClientID EventLoop::getId(void)
{
	return (EVENTLOOP_ID);
}

void EventLoop::receiveMessage(Message msg)
{
	MessageType	type;
	int			fd;

	type = msg.getType();
	fd = msg.getFd();
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
	}
}

/*
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
			_sendMessages(ev);
	}
}
*/

void EventLoop::_registerReadEvent(int fd)
{
	Event*		event;
	EventType	type;

	event = _getEventFromMap(_eventMap, fd);
	if (!event)
	{
		event = new Event(fd, READ_SOCKET);
		_addEventToMap(fd, event);
		sendMessage(Message(CONNECTIONS_ID, fd, CONNECTION_PAUSE_TIMER));
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

void EventLoop::_closeTimeoutEvents(void)
{
	std::map<int, Event*>::iterator	it;
	Event							*event;
	int								fd;
	int								cgiReadFd;
	int								cgiWriteFd;

	if (_eventMap.empty())
		return ;
	for (it = _eventMap.begin(); it != _eventMap.end(); it++)
	{
		event = it->second;
		fd = event->getFd();

		if (fd != it->first)
			continue ;
		//cgiReadFd = event->getCgiReadFd();
		//cgiWriteFd = event->getCgiWriteFd();

		if (event->isEventTimeout())
		{
			if (event->getActualState() != WRITE_EVENT)
			{
				event->setStatusCode(REQUEST_TIMEOUT_CODE);
				event->setActualState(TYPE_TRANSITION);
				_addEventToQueue(event->getFd());
			}
		}

		/*if (event->isEventTimeout())
		{
			if (cgiReadFd > 0)
				sendMessage(new Message(EVENTDEMUX_ID, cgiReadFd, EVENT_REMOVE));
			if (cgiWriteFd > 0)
				sendMessage(new Message(EVENTDEMUX_ID, cgiWriteFd, EVENT_REMOVE));
			sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
			sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
			_deleteEvent(fd);
		}*/
	}
}

void EventLoop::_checkIfCgiScriptsFinished(void)
{
	std::map<int, Event*>::iterator	it;
	std::vector<int>::iterator		itVect;
	std::vector<int>				elmToRemove;
	Event							*event;
	int								fd;

	for (it = _cgiEventMap.begin(); it != _cgiEventMap.end(); it++)
	{
		fd = it->first;
		if (!_getEventFromMap(_eventMap, fd))
			elmToRemove.push_back(fd);
		else
		{
			event = it->second;
			if (event->isCgiScriptEndend())
			{
				event->setActualState(TYPE_TRANSITION);
				_addEventToQueue(fd);
				elmToRemove.push_back(fd);
			}
			else if (CgiExec::isEnded(event))
				event->setCgiScriptEndend(true);
		}
	}
	if (elmToRemove.empty())
		return ;
	for (itVect = elmToRemove.begin(); itVect != elmToRemove.end(); itVect++)
		_cgiEventMap.erase(*itVect);
}

void EventLoop::_finalizeEvent(Event *event)
{
	int	fd;

	fd = event->getFd();
	if (event->isConnectionClose())
		_handleClientDisconnect(event);
	else
		_deleteEvent(fd);
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
	if (!event->isFdRemoved())
	{
		sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
		sendMessage(Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
		event->isFdRemoved();
	}
	if (cgiReadFd > 0 && !event->isCgiReadFdRemoved())
	{
		sendMessage(Message(EVENTDEMUX_ID, cgiReadFd, EVENT_REMOVE));
		event->setCgiReadFdRemoved();
	}
	if (cgiWriteFd > 0 && !event->isCgiWriteFdRemoved())
	{
		sendMessage(Message(EVENTDEMUX_ID, cgiWriteFd, EVENT_REMOVE));
		event->setCgiWriteFdRemoved();
	}
	_deleteEvent(fd);
}

int EventLoop::_getNextEventFromQueue(void)
{
	int fd;

	fd = _eventQueue.front();
	_eventQueue.pop();
	return (fd);
}

void EventLoop::_sendMessages(Event *event)
{
	EventType	type;
	int			fd;
	
	type = event->getActualState();
	fd = event->getFd();
	if (type == WRITE_EVENT)
	{
		if (event->getCgiReadFd() > 0 && !event->isCgiReadFdRemoved())
		{
			sendMessage(Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_REMOVE));
			event->setCgiReadFdRemoved();
		}
		if (event->getCgiWriteFd() > 0 && !event->isCgiWriteFdRemoved())
		{
			sendMessage(Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_REMOVE));
			event->setCgiWriteFdRemoved();
		}
		sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_WRITE));

	}
	else if (type == READ_SOCKET)
	{
		sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_READ));
		sendMessage(Message(CONNECTIONS_ID, fd, CONNECTION_RESTART_TIMER));
	}
	else if (type == WRITE_CGI)
	{
		_cgiEventMap.insert(std::make_pair(event->getFd(), event));
		_eventMap.insert(std::make_pair(event->getCgiWriteFd(), event));
		sendMessage(Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_ADD_NEW));
		sendMessage(Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_CHANGE_TO_WRITE));
	}
	else if (type == READ_CGI)
	{
		if (event->getCgiWriteFd() > 0 && !event->isCgiWriteFdRemoved())
		{
			sendMessage(Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_REMOVE));
			event->setCgiWriteFdRemoved();
		}
		_eventMap.insert(std::make_pair(event->getCgiReadFd(), event));
		sendMessage(Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_ADD_NEW));
	}
}

void EventLoop::_cleanHandlers(void)
{
	std::map<EventType, IEventHandler*>::iterator it;

	for(it = _handlers.begin(); it != _handlers.end(); it++)
		delete it->second;
}

void EventLoop::_cleanEvents(void)
{
	std::map<int, Event*>::iterator	it;
	Event							*event;
	int								fd;

	for(it = _eventMap.begin(); it != _eventMap.end(); it++)
	{
		fd = it->first;
		event = it->second;
		if (fd != event->getFd())
			it->second = NULL;
	}
	for(it = _eventMap.begin(); it != _eventMap.end(); it++)
	{
		if (it->second)
			delete it->second;
	}	
}

void EventLoop::_changeEventStatus(Event *event)
{
	EventType	type;
	int			fd;
	
	if (!event->isStateChange())
		return ;
	event->setIsStateChange(false);
	type = event->getActualState();
	fd = event->getFd();
	if (type == WRITE_EVENT)
	{
		if (event->getCgiReadFd() > 0 && !event->isCgiReadFdRemoved())
		{
			sendMessage(Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_REMOVE));
			event->setCgiReadFdRemoved();
		}
		if (event->getCgiWriteFd() > 0 && !event->isCgiWriteFdRemoved())
		{
			sendMessage(Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_REMOVE));
			event->setCgiWriteFdRemoved();
		}
		sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_WRITE));
	}
	if (type == CLOSE_EVENT)
	{
		sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_READ));
		sendMessage(Message(CONNECTIONS_ID, fd, CONNECTION_RESTART_TIMER));
		_deleteEvent(fd);
	}
	if (type == DISCONNECT_EVENT)
	{
		sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
		sendMessage(Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
		if (event->getCgiReadFd() > 0 && !event->isCgiReadFdRemoved())
		{
			sendMessage(Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_REMOVE));
			event->setCgiReadFdRemoved();
		}
		if (event->getCgiWriteFd() > 0 && !event->isCgiWriteFdRemoved())
		{
			sendMessage(Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_REMOVE));
			event->setCgiWriteFdRemoved();
		}
		_deleteEvent(fd);
	}
}

// DEBUG
void EventLoop::_showEventMap(void)
{
	std::map<int, Event*>::iterator it;

	std::cout << "show _eventMap" << std::endl;
	for (it = _eventMap.begin(); it != _eventMap.end(); it++)
		std::cout << "fd: " << it->first << std::endl;
}

// DEBUG
void EventLoop::_showCgiEventMap(void)
{
	std::map<int, Event*>::iterator it;

	std::cout << "show _cgiEventMap" << std::endl;
	for (it = _cgiEventMap.begin(); it != _cgiEventMap.end(); it++)
		std::cout << it->first << std::endl;
}
