/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/23 18:51:51 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"
#include "Signals.hpp"
#include "CgiExec.hpp"
#include <unistd.h>

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
	_checkIfCgiScriptsFinished();
	_closeTimeoutEvents();
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

void EventLoop::_registerReadEvent(int fd)
{
	Event*		event;
	EventType	type;

	event = _getEventFromMap(_eventMap, fd);
	if (!event)
	{
		event = _createEventObj(fd);
		if (event)
		{
			_insertEventToMap(_eventMap, fd, event);
			sendMessage(Message(CONNECTIONS_ID, fd, CONNECTION_PAUSE_TIMER));
		}
	}
	else if (event)
	{
		type = event->getActualState();
		if ((type == READ_SOCKET && event->getFd() == fd)
			|| (type == READ_CGI && event->getCgiReadFd() == fd))
			_addEventToQueue(fd);
		else
			event->setActualState(DISCONNECT_EVENT);
	}
}

Event* EventLoop::_createEventObj(int fd)
{
	Event*	event;

	event = NULL;
	try {
		event = new Event(fd);
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << BOLDRED << "Webserv: Connection will be closed - Memory Allocation Error" << RESET << std::endl;
		sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
		sendMessage(Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
		close(fd);
	}
	return (event);
}


void EventLoop::_registerWriteEvent(int fd)
{
	Event*		event;
	EventType	type;

	event = _getEventFromMap(_eventMap, fd);
	if (!event)
		return ;
	type = event->getActualState();
	if ((type == WRITE_SOCKET && fd == event->getFd())
		|| (type == WRITE_CGI && fd == event->getCgiWriteFd()))
		_addEventToQueue(fd);
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

void EventLoop::_closeTimeoutEvents(void)
{
	std::map<int, Event*>::iterator	it;
	std::vector<int>::iterator		itVect;
	std::vector<int>				elmWithTimeout;
	Event							*event;
	int								fd;
	EventType						state;

	if (_eventMap.empty())
		return ;
	for (it = _eventMap.begin(); it != _eventMap.end(); it++)
	{
		event = it->second;
		fd = event->getFd();
		if (fd != it->first)
			continue ;
		if (event->isEventTimeout())
		{
			state = event->getActualState();
			if (state == READ_SOCKET)
				event->setStatusCode(REQUEST_TIMEOUT_CODE);
			else if (state == WRITE_CGI || state == READ_CGI)
				event->setStatusCode(GATEWAY_TIMEOUT_CODE);
			if (event->getStatusCode())
				event->setActualState(WRITE_SOCKET);
			else
				event->setActualState(DISCONNECT_EVENT);
			elmWithTimeout.push_back(it->first);
		}
	}
	if (elmWithTimeout.empty())
		return ;
	for (itVect = elmWithTimeout.begin(); itVect != elmWithTimeout.end(); itVect++)
		_changeEventStatus(_getEventFromMap(_eventMap, *itVect));
}

void EventLoop::_checkIfCgiScriptsFinished(void)
{
	std::map<int, Event*>::iterator	it;
	std::vector<int>::iterator		itVect;
	std::vector<int>				elmToRemove;
	Event							*event;
	int								fd;
	
	if (_cgiEventMap.empty())
		return ;
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
				event->setActualState(WRITE_SOCKET);
				elmToRemove.push_back(fd);
			}
			else if(CgiExec::isEnded(event))
				event->setCgiScriptEndend(true);
		}
	}
	if (elmToRemove.empty())
		return ;
	for (itVect = elmToRemove.begin(); itVect != elmToRemove.end(); itVect++)
		_changeEventStatus(_getEventFromMap(_cgiEventMap, *itVect));
}

int EventLoop::_getNextEventFromQueue(void)
{
	int fd;

	fd = _eventQueue.front();
	_eventQueue.pop();
	return (fd);
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

	if (!event)
		return ;
	if (!event->isStateChange())
		return ;
	event->setIsStateChange(false);
	type = event->getActualState();
	if (type == WRITE_CGI)
		_changeToWriteCgi(event);
	if (type == READ_CGI)
		_changeToReadCgi(event);
	if (type == WRITE_SOCKET)
		_changeToWriteSocket(event);
	if (type == CLOSE_EVENT)
		_closeEvent(event);
	if (type == DISCONNECT_EVENT)
		_disconnectEvent(event);
}

void EventLoop::_changeToWriteCgi(Event *event)
{
	int fd;

	if (CgiExec::execute(event) == -1)
	{
		event->setStatusCode(INTERNAL_SERVER_ERROR_CODE);
		event->setActualState(WRITE_SOCKET);
	}
	else
	{
		fd = event->getCgiWriteFd();
		_insertEventToMap(_cgiEventMap, event->getFd(), event);
		_insertEventToMap(_eventMap, fd, event);
		sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_ADD_NEW));
		sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_WRITE));
		event->setCgiFdRemoved(fd, false);
	}
	//event->setIsStateChange(false);
}

void EventLoop::_changeToReadCgi(Event *event)
{
	int readFd;
	int writeFd;

	readFd = event->getCgiReadFd();
	writeFd = event->getCgiWriteFd();
	if (writeFd > 0 && !event->isCgiWriteFdRemoved())
	{
		sendMessage(Message(EVENTDEMUX_ID, writeFd, EVENT_REMOVE));
		event->setCgiFdRemoved(writeFd, true);
	}
	if (writeFd > 0)
		_eventMap.erase(writeFd);
	_insertEventToMap(_eventMap, readFd, event);
	sendMessage(Message(EVENTDEMUX_ID, readFd, EVENT_ADD_NEW));
	event->setCgiFdRemoved(readFd, false);
	event->setIsStateChange(false);
}

void EventLoop::_changeToWriteSocket(Event *event)
{
	_removeAllCgiFds(event);
	sendMessage(Message(EVENTDEMUX_ID, event->getFd(), EVENT_CHANGE_TO_WRITE));
	event->setIsStateChange(false);
}

void EventLoop::_closeEvent(Event *event)
{
	int fd;

	fd = event->getFd();
	sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_READ));
	sendMessage(Message(CONNECTIONS_ID, fd, CONNECTION_RESTART_TIMER));
	_removeAllCgiFds(event);
	_deleteEvent(fd);
}

void EventLoop::_disconnectEvent(Event *event)
{
	int fd;

	fd = event->getFd();
	sendMessage(Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
	sendMessage(Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
	_removeAllCgiFds(event);
	_deleteEvent(fd);
}

void EventLoop::_insertEventToMap(std::map<int, Event*> &map, int fd, Event *event)
{
	if (event)
		map.insert(std::make_pair(fd, event));
}

void EventLoop::_removeCgiFd(Event *event, int cgiFd)
{
	if (cgiFd > 0 && !event->isCgiFdRemoved(cgiFd))
	{
		sendMessage(Message(EVENTDEMUX_ID, cgiFd, EVENT_REMOVE));
		event->setCgiFdRemoved(cgiFd, true);
	}
	_eventMap.erase(cgiFd);
}

void EventLoop::_removeAllCgiFds(Event *event)
{
	int	fd;

	fd = event->getFd();
	if (!event)
		return ;
	_removeCgiFd(event, event->getCgiWriteFd());
	_removeCgiFd(event, event->getCgiReadFd());
	_cgiEventMap.erase(fd);
}

void EventLoop::_deleteEvent(int fd)
{
	Event*	event;

	event = _getEventFromMap(_eventMap, fd);
	if (event)
		delete event;
	_eventMap.erase(fd);
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
