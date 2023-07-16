/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/16 10:35:31 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"

#include "CGIExecuter.hpp"

EventLoop::EventLoop(void): AMessengerClient(NULL) {}

EventLoop::EventLoop(const EventLoop &src) {}

EventLoop::~EventLoop(void) {}

// Mudar nome do parametro para "IEventHandler *eventHandler"
void EventLoop::registerEventHandler(IEventHandler *event)
{
	EventType type;
	
	type = event->getHandleType();
	_handlers.insert(std::make_pair(type, event));
}

void EventLoop::unregisterEventHandler(IEventHandler *event)
{
	_handlers.erase(event->getHandleType());
}

/*
void EventLoop::handleEvents(void)
{
	// std::cout << "_eventMap size: " << _eventMap.size() << std::endl;

	Event	*ev;
	while (!_eventQueue.empty())
	{		
		ev = _eventQueue.front();

		if (ev->isEventTimeout() || ev->isClientClosed())
		{
			std::cout << "Event Time Out: " << ev->getFd() << std::endl;
			//sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), CLOSE_CONNECTION));
			sendMessage(new Message(CONNECTIONS_ID, ev->getFd(), CONNECTION_REMOVE));
			sendMessage(new Message(EVENTDEMUX_ID, ev->getFd(), EVENT_REMOVE));
			_eventQueue.pop();
			_eventMap.erase(ev->getFd());
			delete ev;
			continue;
		}

		//initState = ev->getState();

		_handleEvent(ev);
		_eventQueue.pop();

		if (ev->getState() == COMPLETE_EVENT)
		{
			//std::cout << counter++ << " - Request/Response Complete" << std::endl;
			sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), READ_EVENT, CHANGE_EVENT));
			if (ev->isConnectionClose())
				sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), CLOSE_CONNECTION));
			else
				sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), PAUSED));
			_eventMap.erase(ev->getFd());
			delete ev;	
		}
		else if (ev->getState() == CGI_EVENT)
		{
			std::cout << "State: " << ev->getState() << std::endl;

			if (ev->getCgiFd() == -1)
			{
				ev->setCgiEx(new CGIExecuter());
				std::cout << "FD CGI: " << ev->getCgiFd() << std::endl;
				_eventMap.insert(std::make_pair(ev->getCgiFd(), ev));
				_eventQueue.push(ev);
				sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getCgiFd(), READ_EVENT, NEW_EVENT));
			}
			//ev->setState(CGI_EXECUTION);
		}
		else
			sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), ev->getState(), CHANGE_EVENT));
	}
}
*/

void EventLoop::handleEvents(void)
{
	Event	*event;
	while (!_eventQueue.empty())
	{		
		event = _eventQueue.front();
		_handleEvent(event);
		_eventQueue.pop();
		_handleEventStates(event);
	}
}

ClientID EventLoop::getId(void)
{
	return (EVENTLOOP_ID);
}

/*
void EventLoop::receiveMessage(Message *msg)
{
	std::map<int, Event*>::iterator	it;
	EventMessage					*m;
	int								fd;

	m = dynamic_cast<EventMessage*>(msg);
	if (!m)
		return ;
	_handleMessage(m);
}


// Modificar isto o change event não deve existir apenas deve existir o add new event
void EventLoop::_handleMessage(EventMessage *msg)
{
	std::map<int, Event*>::iterator	it;
	int								fd;

	fd = msg->getFd();

	it = _eventMap.find(fd);
	if (it == _eventMap.end())
		_addNewEvent(new Event(fd, msg->getEvent()));
	else if (it->second->getState() != CGI_EVENT)
		_changeEvent(it->second, msg->getEvent());
	else if (it->second->getState() == CGI_EVENT)
		_eventQueue.push(it->second);
}
*/

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


/*
void EventLoop::_addNewEvent(Event *ev)
{
	_eventMap.insert(std::make_pair(ev->getFd(), ev));
	_eventQueue.push(ev);
	sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), PROCESSING));
}
*/

/*
void EventLoop::_changeEvent(Event *ev, short status)
{
	ev->setState(status);
	_eventQueue.push(ev);
}
*/

void EventLoop::_handleEvent(Event *ev)
{
	std::map<EventType, IEventHandler*>::iterator it;
	
	it = _handlers.find((EventType)ev->getState());
	if (it != _handlers.end())
		it->second->handleEvent(ev);
}

/*
void EventLoop::_addNewEvent(int fd)
{
	_eventMap.insert(std::make_pair(ev->getFd(), ev));
	_eventQueue.push(ev);
	sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), PROCESSING));
}
*/

Event* EventLoop::_getEventFromMap(int fd)
{
	std::map<int, Event*>::iterator	it;

	it = _eventMap.find(fd);
	if (it != _eventMap.end())
		return (it->second);
	return (NULL);
}

void EventLoop::_addEventToMap(Event *event)
{
	int	fd;

	fd = event->getFd();
	_eventMap.insert(std::make_pair(fd, event));
}

void EventLoop::_addEventToQueue(Event *event)
{
	_eventQueue.push(event);
}

void EventLoop::_registerReadEvent(int fd)
{
	Event*	event;

	event = _getEventFromMap(fd);
	if (!event)
	{
		event = new Event(fd, READ_EVENT);
		_addEventToMap(event);
		sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_PAUSE_TIMER));
	}
	if (event->getState() == READ_EVENT || event->getState() == CGI_EVENT)
		_addEventToQueue(event);
}

void EventLoop::_registerWriteEvent(int fd)
{
	Event*	event;

	event = _getEventFromMap(fd);
	if (event && event->getState() == WRITE_EVENT)
		_addEventToQueue(event);
}

void EventLoop::_deleteEvent(int fd)
{
	Event*	event;

	event = _getEventFromMap(fd);
	if (event)
	{
		_eventMap.erase(fd);
		delete event;	
	}
}

void EventLoop::_handleEventStates(Event *event)
{
	int fd;

	fd = event->getFd();
	if (event->getState() == READ_EVENT_COMPLETE)
	{
		event->setState(WRITE_EVENT);
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_WRITE));
	}
	else if (event->getState() == WRITE_EVENT_COMPLETE)
	{
		_deleteEvent(event->getFd());
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_READ));
		sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_RESTART_TIMER));
	}
	else if (event->getState() == CGI_EVENT_COMPLETE)
		; // Pass event to Write and remove from map
	else if (event->getState() == CLOSED_EVENT)
	{
		_deleteEvent(event->getFd());
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
		sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
	}
		; // delete and send messages to remove from EVENTDEMUX and CONNECTIONS	
}
