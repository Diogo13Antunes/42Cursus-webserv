/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventDemux.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:10:06 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/15 11:30:06 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventDemux.hpp"

EventDemux::EventDemux(void): AMessengerClient(NULL) {}

EventDemux::~EventDemux(void) {}

ClientID EventDemux::getId(void)
{
	return (EVENTDEMUX_ID);
}

void EventDemux::init(std::map<int, struct sockaddr_in> servers)
{
	std::map<int, struct sockaddr_in>::iterator it;

	_servers = servers;
	_epollFd = epoll_create1(0);
	for (it = _servers.begin(); it != _servers.end(); it++)
		_addNewEvent(it->first);
}

void EventDemux::waitAndDispatchEvents(void)
{
	int		numEvents;
	int		eventFd;
	int		newClientFd;

	numEvents = epoll_wait(_epollFd, _events, EPOLL_MAX_NEVENTS, EPOLL_TIMEOUT);
	for (int i = 0; i < numEvents; i++) 
	{
		eventFd = _events[i].data.fd;
		newClientFd = _acceptClientConnectionIfServer(eventFd);
		if (newClientFd != -1)
		{
			_addNewEvent(newClientFd);
			sendMessage(Message(CONNECTIONS_ID, newClientFd, CONNECTION_ADD_NEW));
		}
		else
		{
			if (_isReadEvent(_events[i].events))
				sendMessage(Message(EVENTLOOP_ID, eventFd, EVENT_READ_TRIGGERED));

			else if (_isWriteEvent(_events[i].events))
				sendMessage(Message(EVENTLOOP_ID, eventFd, EVENT_WRITE_TRIGGERED));
		}
	}
}

void EventDemux::receiveMessage(Message msg)
{
	MessageType	type;
	int			fd;

	type = msg.getType();
	fd = msg.getFd();
	if (type == EVENT_ADD_NEW)
		_addNewEvent(fd);
	else if (type == EVENT_CHANGE_TO_READ)
		_changeEvent(fd, EPOLLIN);
	else if (type == EVENT_CHANGE_TO_WRITE)
		_changeEvent(fd, EPOLLOUT);
	else if (type == EVENT_REMOVE)
		_removeEvent(fd);
}

void EventDemux::_addNewEvent(int fd)
{
	struct epoll_event	ev;
	int					flags;

	ev.data.fd = fd;
    //ev.events = EPOLLIN | EPOLLOUT;
	ev.events = EPOLLIN;
	flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &ev) == -1)
		std::cerr << "Failed to add socket to epoll." << std::endl;
}

void EventDemux::_removeEvent(int fd)
{
	if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, NULL) == -1)
		std::cerr << "Failed to remove event from epoll" << std::endl;
}

void EventDemux::_changeEvent(int fd, uint32_t eventMask)
{
	struct epoll_event	ev;

    ev.data.fd = fd;
    //ev.events = EPOLLIN | EPOLLOUT;
	ev.events = eventMask;
	if (epoll_ctl(_epollFd, EPOLL_CTL_MOD, fd, &ev) == -1)
		std::cerr << "Failed to modify socket to epoll." << std::endl;
}

bool EventDemux::_isReadEvent(uint32_t eventMask)
{
	if (eventMask & EPOLLIN)
		return (true);
	return (false);
}

bool EventDemux::_isWriteEvent(uint32_t eventMask)
{
	if (eventMask & EPOLLOUT)
		return (true);
	return (false);
}

int EventDemux::_acceptClientConnectionIfServer(int fd)
{
	std::map<int, struct sockaddr_in>::iterator	it;
	struct sockaddr_in							addr;
	socklen_t									addrlen;
	int 										serverFd;
	int											clientFd;
	
	it = _servers.find(fd);
	if (it == _servers.end())
		return (-1);
	serverFd = it->first;
	addr = it->second;
	addrlen = (socklen_t)sizeof(addr);
	clientFd = accept(serverFd, (struct sockaddr *) &addr, &addrlen);
	return (clientFd);
}
