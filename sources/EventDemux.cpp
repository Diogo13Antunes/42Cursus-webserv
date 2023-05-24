/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventDemux.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:10:06 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/24 17:50:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventDemux.hpp"

EventDemux::EventDemux(void)
{
	//Default EventDemultiplexer Constructor
}

EventDemux::EventDemux(Messenger *messenger)
{

}

// missing get errors of epoll functions and handle
EventDemux::EventDemux(int serverFd, struct sockaddr_in address, socklen_t addrlen):
	_serverFd(serverFd),
	_address(address),
	_addrlen(addrlen)
{
	epoll_event event;

	_epollFd = epoll_create1(0);
	_addNewFdToEventList(serverFd);
}

EventDemux::EventDemux(const EventDemux &src)
{
	//EventDemultiplexer Copy Constructor
}

EventDemux::~EventDemux(void)
{
	//Default EventDemultiplexer Destructor
}

/*
EventDemux &EventDemux::operator=(const EventDemux &src)
{
	//EventDemultiplexer Copy Assignment Operator
}
*/

void EventDemux::setServerFd(int serverFd)
{
	_serverFd = serverFd;
}

void EventDemux::setMessenger(Messenger *messenger)
{
	_messenger = messenger;
}

void EventDemux::waitAndDispatchEvents(void)
{
	int		numEvents;
	int		newFd;
	t_msg	msg;

	numEvents = epoll_wait(_epollFd, _events, N_MAX_EVENTS, -1);
	for (int i = 0; i < numEvents; i++) 
	{
		if (_events[i].data.fd == _serverFd)
		{
			newFd = accept(_serverFd, (struct sockaddr *) &_address, &_addrlen);
			_addNewFdToEventList(newFd);
			msg.dst = CONNECTIONS_ID;
			msg.fd = newFd;
			_sendMessage(msg);
		}
		else 
		{
			msg.dst = EVENTLOOP_ID;
			msg.fd = _events[i].data.fd;
			_sendMessage(msg);
		}
	}
}

ModuleID EventDemux::getId(void)
{
	return (EVENTDEMUX_ID);
}

void EventDemux::handleMessage(t_msg msg)
{
	std::cout << "EventDemux receive mensage" << std::endl;
}

void EventDemux::_addNewFdToEventList(int fd)
{
	epoll_event	event;
		
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLOUT | EPOLLET;
	epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &event);	
}

void	EventDemux::_sendMessage(t_msg msg)
{
	_messenger->sendMessage(msg);
}
