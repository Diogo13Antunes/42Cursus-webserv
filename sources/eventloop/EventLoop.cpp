/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/31 18:11:49 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"

EventLoop::EventLoop(void): AMessengerClient(NULL) {}

EventLoop::EventLoop(const EventLoop &src) {}

EventLoop::~EventLoop(void) {}

/*
EventLoop &EventLoop::operator=(const EventLoop &src)
{
	//EventLoop Copy Assignment Operator
}
*/

void EventLoop::registerEvent(IEventHandler *event)
{
	EventType type;
	
	type = event->getHandleType();
	_handlers.insert(std::make_pair(type, event));
}

void EventLoop::unregisterEvent(IEventHandler *event)
{
	_handlers.erase(event->getHandleType());
}

void EventLoop::handleEvents(void)
{
	Event	*ev;

	while (!_eventQueue.empty())
	{
		ev = _handleNextEvent();
		if ((EventType)ev->getState() == READ_EVENT)
			sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), WRITE_EVENT));
		else if ((EventType)ev->getState() == WRITE_EVENT)
		{
			sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), READ_EVENT));
			_eventMap.erase(ev->getFd());
			delete ev;
		}
	}
}

ClientID EventLoop::getId(void)
{
	return (EVENTLOOP_ID);
}

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

void EventLoop::_handleMessage(EventMessage *msg)
{
	std::map<int, Event*>::iterator	it;
	int								fd;

	fd = msg->getFd();
	it = _eventMap.find(fd);
	if (it == _eventMap.end())
		_addNewEvent(new Event(fd, msg->getEvent()));
	else 
		_changeEvent(it->second, msg->getEvent());	
}

void EventLoop::_addNewEvent(Event *ev)
{
	_eventMap.insert(std::make_pair(ev->getFd(), ev));
	_eventQueue.push(ev);
}

void EventLoop::_changeEvent(Event *ev, short status)
{
	ev->setState(status);
	_eventQueue.push(ev);
}

Event* EventLoop::_handleNextEvent(void)
{
	Event	*ev;

	ev = _eventQueue.front();
	_handlers.find((EventType)ev->getState())->second->handleEvent(ev);
	_eventQueue.pop();
	return (ev);
}
