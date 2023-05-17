/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/17 19:05:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"

EventLoop::EventLoop(void)
{
	//Default EventLoop Constructor
}

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

	_handlers.insert(std::pair<EventType, IEventHandler*>(event->getHandleType(), event));
}

void EventLoop::unregisterEvent(IEventHandler *event)
{
	_handlers.erase(event->getHandleType());
}

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
