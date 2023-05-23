/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/23 10:31:03 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"
#include "Event.hpp"

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

void EventLoop::handleEvents(void)
{
	Event											*ev;
	t_msg											msg;

	if (_readQueue.size())
	{
		ev = _readQueue.front();
		 _handlers.find(READ_EVENT)->second->handleEvent(ev);
		_readQueue.pop();
		ev->setState(0);

		// Important: can only send the message after ensuring that you have nothing else to read. 
		// hadle later.

		msg.dst = CONNECTIONS_ID;
		msg.fd = ev->getFd();
		msg.event = POLLOUT;
		_sendMessage(msg);
	}
	if (_writeQueue.size())
	{
		ev = _writeQueue.front();
		_handlers.find(WRITE_EVENT)->second->handleEvent(ev);
		_writeQueue.pop();

		msg.dst = CONNECTIONS_ID;
		msg.fd = ev->getFd();
		msg.event = POLLIN;
		_sendMessage(msg);

		_eventsMap.erase(ev->getFd());
		delete ev;
	}
}

ModuleID EventLoop::getId(void)
{
	return (EVENTLOOP_ID);
}

void EventLoop::handleMessage(t_msg msg)
{
	if (msg.event == POLLIN)
		_addNewEventReadPoll(msg.fd, msg.event);
	else if (msg.event == POLLOUT)
		_addNewEventWritePoll(msg.fd, msg.event);
}

void EventLoop::_sendMessage(t_msg msg)
{
	_messenger->sendMessage(msg);
}

void EventLoop::_addNewEventReadPoll(int fd, short event)
{
	Event *ev;

	// IMPORTANT: What happens if event is from read and is in the map as hide or write ?

	if (_eventsMap.empty() || _eventsMap.find(fd) == _eventsMap.end())
	{
		ev = new Event(fd, event);
		_eventsMap.insert(std::pair<int,Event*>(fd, ev));
		_readQueue.push(ev);
	}
}

void EventLoop::_addNewEventWritePoll(int fd, short event)
{
	std::map<int, Event*>::iterator it;

	if (_eventsMap.empty()) //there must have been reading first. have to throw error ?
		return ;
	it = _eventsMap.find(fd);
	if (it != _eventsMap.end())
	{
		if (it->second->getState() == 0)
		{
			it->second->setState(event);
			_writeQueue.push(it->second);
		}
	}
}