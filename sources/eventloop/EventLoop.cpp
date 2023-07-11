/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/11 18:04:17 by dcandeia         ###   ########.fr       */
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

void EventLoop::handleEvents(void)
{
	// std::cout << "_eventMap size: " << _eventMap.size() << std::endl;

	Event	*ev;
	while (!_eventQueue.empty())
	{		
		ev = _eventQueue.front();

		// std::cout << "FD do Evento: " << ev->getFd() << " Estado: " << ev->getState() << std::endl;	

		if (ev->isEventTimeout())
		{
			std::cout << "Event Time Out: " << ev->getFd() << std::endl;
			sendMessage(new ConnectionMessage(CONNECTIONS_ID, ev->getFd(), CLOSE_CONNECTION));
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
	else if (it->second->getState() != CGI_EVENT)
		_changeEvent(it->second, msg->getEvent());
	else if (it->second->getState() == CGI_EVENT)
		_eventQueue.push(it->second);
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
	std::map<EventType, IEventHandler*>::iterator it;
	
	//std::cout << "State Event Loop: "  << (EventType)ev->getState() << std::endl;
	
	it = _handlers.find((EventType)ev->getState());
	if (it != _handlers.end())
		it->second->handleEvent(ev);
	//else
		//std::cout << "State Event Loop: Não encontrou handler -> "  << (EventType)ev->getState() << std::endl;

}