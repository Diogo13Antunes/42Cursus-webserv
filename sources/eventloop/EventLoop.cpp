/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/26 15:33:26 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"

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

void EventLoop::handleEvents(void)
{
	Event	*ev;
	while (!_eventQueue.empty())
	{		
		ev = _eventQueue.front();

		_handleEvent(ev);
		_eventQueue.pop();


		if (ev->getState() == COMPLETE_EVENT)
		{
			sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), READ_EVENT));
			_eventMap.erase(ev->getFd());
			delete ev;		
		}
		else if (ev->getState() == CGI_EVENT)
		{
			
			//sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), ev->getState()));
		}
		else
			sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), ev->getState()));
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


// Modificar isto o change event não deve existir apenas deve existir o add new event
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


void EventLoop::_handleEvent(Event *ev)
{
	_handlers.find((EventType)ev->getState())->second->handleEvent(ev);
}