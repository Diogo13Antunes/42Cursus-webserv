/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventDemux.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:10:06 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/28 14:14:29 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventDemux.hpp"

EventDemux::EventDemux(void): AMessengerClient(NULL)
{
	//Default EventDemultiplexer Constructor
}

// missing get errors of epoll functions and handle
EventDemux::EventDemux(int serverFd, struct sockaddr_in address, socklen_t addrlen):
	AMessengerClient(NULL),
	_serverFd(serverFd),
	_address(address),
	_addrlen(addrlen)
{
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

/*
void EventDemux::setMessenger(Messenger *messenger)
{
	_messenger = messenger;
}
*/

void EventDemux::waitAndDispatchEvents(void)
{
	int		numEvents;
	int		newFd;
	t_msg	msg;

	std::cout << "Wait New Events" <<std::endl;
	numEvents = epoll_wait(_epollFd, _events, N_MAX_EVENTS, 1000);
	for (int i = 0; i < numEvents; i++) 
	{
		if (_events[i].data.fd == _serverFd)
		{
			newFd = accept(_serverFd, (struct sockaddr *) &_address, &_addrlen);
			_addNewFdToEventList(newFd);
			msg.dst = CONNECTIONS_ID;
			msg.fd = newFd;
			msg.type = 0;
			sendMessage(msg);
			_events[i].events = 0;
		}
		else 
		{
			//Preciso criar mensagens através de herança para defenir tipos
			msg.dst = EVENTLOOP_ID;
			msg.fd = _events[i].data.fd;
			std::cout << "EventDemux: fd: "<< _events[i].data.fd << " events: " << _events[i].events <<std::endl;
			if (_events[i].events & EPOLLIN)
			{
				msg.event = READ;
				std::cout << "EventDemux: evento leitura: "<< msg.event <<std::endl;
			}
			else if (_events[i].events & EPOLLOUT)
			{
				msg.event = WRITE;
				std::cout << "EventDemux: evento escrita: " << msg.event << std::endl;
			}
			
			sendMessage(msg);

			msg.dst = CONNECTIONS_ID;
			msg.type = 1;
			sendMessage(msg);
		}
	}
}

ClientID EventDemux::getId(void)
{
	return (EVENTDEMUX_ID);
}

void EventDemux::receiveMessage(t_msg msg)
{
	std::cout << "EventDemux receive mensage: FD: " << msg.fd << " event: " << msg.event << std::endl;

	if (msg.type == 0)
	{
		if (msg.event == 0)
			_changeFdIntoEventList(msg.fd, EPOLLIN);
		else 
			_changeFdIntoEventList(msg.fd, EPOLLOUT);
	}
	else if (msg.type == 1)
	{
		_removeFdFromEventList(msg.fd);
	}
}

void EventDemux::_addNewFdToEventList(int fd)
{
	int	flags;
		
    _event.data.fd = fd;
    _event.events = EPOLLIN;
	flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &_event) == -1)
		std::cerr << "Failed to add socket to epoll." << std::endl;
}

void EventDemux::_removeFdFromEventList(int fd)
{
	if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, NULL) == -1) {
		std::cerr << "Failed to remove event from epoll" << std::endl;
	}	
}

void EventDemux::_changeFdIntoEventList(int fd, int event)
{
    _event.data.fd = fd;
    _event.events = event;
	if (epoll_ctl(_epollFd, EPOLL_CTL_MOD, fd, &_event) == -1)
		std::cerr << "Failed to modify socket to epoll." << std::endl;
}
