/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/20 18:23:41 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"

EventLoop::EventLoop(void)
{
	//Default EventLoop Constructor
}

EventLoop::EventLoop(Messenger *messenger):
	_messenger(messenger)
{}

EventLoop::EventLoop(const EventLoop &src)
{
	//EventLoop Copy Constructor
}

EventLoop::~EventLoop(void)
{
	//Default EventLoop Destructor
}

/*
EventLoop &EventLoop::operator=(const EventLoop &src)
{
	//EventLoop Copy Assignment Operator
}
*/

void EventLoop::registerEvent(IEventHandler *event)
{
	EventType type = event->getHandleType();

	_handlers.insert(std::pair<EventType, IEventHandler*>(type, event));
}

void EventLoop::unregisterEvent(IEventHandler *event)
{
	_handlers.erase(event->getHandleType());
}

/*
void EventLoop::handleEvents(void)
{
	std::map<EventType, IEventHandler*>::iterator it;
	
	EventType type;

	type = READ_EVENT;
	it = _handlers.find(type);
	it->second->handleEvent();

	type = WRITE_EVENT;
	it = _handlers.find(type);
	it->second->handleEvent();
}
*/


// test queue events
/*void EventLoop::handleEvents(void)
{
	std::map<EventType, IEventHandler*>::iterator it;

	std::cout << "-----event_size " << _events.size() << std::endl;

	if (_events.size() > 2)
	{
		while (true)
		{
			it = _handlers.find(READ_EVENT);
			it->second->handleEvent(_events.front());
			_events.pop();
			if (_events.size() == 0)
				break;
		}
	}
}*/

void EventLoop::handleEvents(void)
{
	std::map<EventType, IEventHandler*>::iterator it;

	t_msg msg;

	if (_events.size())
	{
		it = _handlers.find(READ_EVENT);
		it->second->handleEvent(_events.front());
		_events.pop();

		msg.dest = CONNECTIONS_ID;
		msg.msg = "It's me EventLoop, processing Events";
		_sendMessage(msg);
	}
}

void EventLoop::addNewEvent(int event)
{
	_events.push(event);
}

ModuleID EventLoop::getId(void)
{
	return (EVENTLOOP_ID);
}

void EventLoop::handleMessage(t_msg msg)
{
	std::cout << "Menssage reived by EventLoop: msg: " << msg.msg << std::endl;
}

void	EventLoop::_sendMessage(t_msg msg)
{
	_messenger->sendMessage(msg);
}