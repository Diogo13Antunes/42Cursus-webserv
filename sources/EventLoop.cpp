/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/31 11:03:07 by dsilveri         ###   ########.fr       */
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

	while (!_eventQueue.empty())
	{
		ev = _eventQueue.front();
		_handlers.find((EventType)ev->getState())->second->handleEvent(ev);
		_eventQueue.pop();

		// to do this you need to check that you have read or written everything. For now it stays like this
		//msg.dst = EVENTDEMUX_ID;
		//msg.fd = ev->getFd();
		//msg.type = 0;
		if ((EventType)ev->getState() == READ_EVENT)
		{
			//msg.event = WRITE_EVENT;
			//sendMessage(msg);
			sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), WRITE_EVENT));
		}
		else if ((EventType)ev->getState() == WRITE_EVENT)
		{
			//msg.event = READ_EVENT;
			//sendMessage(msg);
			sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), READ_EVENT));
			_eventsMap.erase(ev->getFd());
			delete ev;
		}
	}
}

ClientID EventLoop::getId(void)
{
	return (EVENTLOOP_ID);
}

/*
void EventLoop::receiveMessage(Message *msg)
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
*/

void EventLoop::receiveMessage(Message *msg)
{
	std::map<int, Event*>::iterator	it;
	EventMessage					*m;
	int								fd;

	m = dynamic_cast<EventMessage*>(msg);
	if (!m)
		return ;
	fd = m->getFd();
	it = _eventsMap.find(m->getFd());
	if (it == _eventsMap.end())
	{
		Event *ev = new Event(fd, m->getEvent());
		_eventsMap.insert(std::make_pair(fd, ev));
		_eventQueue.push(ev);
	}
	else 
	{
		it->second->setState(m->getEvent());
		_eventQueue.push(it->second);
	}
}

