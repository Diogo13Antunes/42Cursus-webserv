/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/11 08:45:59 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"

EventLoop::EventLoop(void): AMessengerClient(NULL) {}

EventLoop::EventLoop(const EventLoop &src) {}

EventLoop::~EventLoop(void) {}

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

	//static int counter = 0;
	
	std::cout << "_eventMap size: " << _eventMap.size() << std::endl;

	Event	*ev;
	//short	initState; //have to be EventType

	while (!_eventQueue.empty())
	{		
		ev = _eventQueue.front();

		if (ev->isEventTimeout() || ev->isClientClosed())
		{
			std::cout << "Event Time Out: " << ev->getFd() << std::endl;
			sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), CLOSE_CONNECTION));
			_eventQueue.pop();
			_eventMap.erase(ev->getFd());
			delete ev;
			continue;
		}

		//initState = ev->getState();

		//std::cout << "evento state: " << initState << std::endl;

		//std::cout << ev->getState() << std::endl;
		_handleEvent(ev);
		_eventQueue.pop();
		

		//sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), ev->getState()));

		if (ev->getState() == COMPLETE_EVENT)
		{
			

			//std::cout << counter++ << " - Request/Response Complete" << std::endl;
			sendMessage(new EventMessage(EVENTDEMUX_ID, ev->getFd(), READ_EVENT));
			if (ev->isConnectionClose())
				sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), CLOSE_CONNECTION));
			else
				sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), PAUSED));
			_eventMap.erase(ev->getFd());
			delete ev;	
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
	sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), PROCESSING));
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