/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/28 10:04:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"
#include "Event.hpp"

EventLoop::EventLoop(void): AMessengerClient(NULL)
{
	//Default EventLoop Constructor
}

/*
EventLoop::EventLoop(Messenger *messenger)
{}
*/

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

void EventLoop::handleEvents(void)
{
	Event	*ev;
	t_msg	msg;

	while (!_eventQueue.empty())
	{
		ev = _eventQueue.front();
		_handlers.find((EventType)ev->getState())->second->handleEvent(ev);
		_eventQueue.pop();

		// to do this you need to check that you have read or written everything. For now it stays like this
		msg.dst = EVENTDEMUX_ID;
		msg.fd = ev->getFd();
		msg.type = 0;
		if ((EventType)ev->getState() == READ_EVENT)
		{
			msg.event = WRITE_EVENT;
			sendMessage(msg);
		}
		else if ((EventType)ev->getState() == WRITE_EVENT)
		{
			msg.event = READ_EVENT;
			sendMessage(msg);
			_eventsMap.erase(ev->getFd());
			delete ev;
		}
	}
}

ClientID EventLoop::getId(void)
{
	return (EVENTLOOP_ID);
}

void EventLoop::receiveMessage(t_msg msg)
{
	std::map<int, Event*>::iterator it;

	std::cout << "EventLoop: fd: " << msg.fd << " event: " << msg.event << std::endl;

	it = _eventsMap.find(msg.fd);
	if (it == _eventsMap.end())
	{
		Event *ev = new Event(msg.fd, (int)msg.event);
		_eventsMap.insert(std::pair<int,Event*>(msg.fd, ev));
		_eventQueue.push(ev);
	}
	else 
	{
		it->second->setState(msg.event);
		_eventQueue.push(it->second);
	}
}

/*
void EventLoop::_sendMessage(t_msg msg)
{
	_messenger->sendMessage(msg);
}
*/