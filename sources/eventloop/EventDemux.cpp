/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventDemux.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:10:06 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/14 16:03:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventDemux.hpp"

EventDemux::EventDemux(void): AMessengerClient(NULL) {}

EventDemux::EventDemux(int serverFd, struct sockaddr_in address, socklen_t addrlen):
	AMessengerClient(NULL),
	_serverFd(serverFd),
	_address(address),
	_addrlen(addrlen)
{
	_epollFd = epoll_create1(0);
	_addNewEvent(serverFd);
}

EventDemux::~EventDemux(void){}

ClientID EventDemux::getId(void)
{
	return (EVENTDEMUX_ID);
}

void EventDemux::waitAndDispatchEvents(void)
{
	int		numEvents;
	int		eventFd;
	int		timeOutMs;

	timeOutMs = 1000;
	numEvents = epoll_wait(_epollFd, _events, N_MAX_EVENTS, timeOutMs);
	for (int i = 0; i < numEvents; i++) 
	{
		eventFd = _events[i].data.fd;
		if (eventFd == _serverFd)
		{
			eventFd = accept(_serverFd, (struct sockaddr *) &_address, &_addrlen);
			if (eventFd != -1)
			{
				_addNewEvent(eventFd);
				sendMessage(new Message(CONNECTIONS_ID, eventFd, CONNECTION_ADD_NEW));
			}
		}
		else
		{
			if (_getEventType(_events[i].events) == READ_EVENT)
			{
				sendMessage(new Message(EVENTLOOP_ID, eventFd, EVENT_READ_TRIGGERED));
				sendMessage(new Message(CONNECTIONS_ID, eventFd, CONNECTION_RESET_TIMER));
			}
			else if (_getEventType(_events[i].events) == WRITE_EVENT)
			{
				sendMessage(new Message(EVENTLOOP_ID, eventFd, EVENT_WRITE_TRIGGERED));
				sendMessage(new Message(CONNECTIONS_ID, eventFd, CONNECTION_RESET_TIMER));
			}
			else
				; //error provavelmente fechar a ligação 
		}
	}
}

void EventDemux::receiveMessage(Message *msg)
{
	MessageType	type;
	int			fd;

	type = msg->getType();
	fd = msg->getFd();
	if (type == EVENT_ADD_NEW)
		_addNewEvent(fd);
	else if (type == EVENT_CHANGE_TO_READ)
		_changeEvent(fd, READ_EVENT);
	else if (type == EVENT_CHANGE_TO_WRITE)
		_changeEvent(fd, WRITE_EVENT);
	else if (type == EVENT_REMOVE)
		_removeEvent(fd);
}

void EventDemux::_addNewEvent(int fd)
{
	struct epoll_event	ev;
	int					flags;

	ev.data.fd = fd;
    ev.events = EPOLLIN;
	flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &ev) == -1)
		std::cerr << "Failed to add socket to epoll." << std::endl;
}

void EventDemux::_removeEvent(int fd)
{
	if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, NULL) == -1) {
		std::cerr << "Failed to remove event from epoll" << std::endl;
	}	
}

void EventDemux::_changeEvent(int fd, EventType eventType)
{
	struct epoll_event	ev;

    ev.data.fd = fd;
    ev.events = _getEventsMask(eventType) | EPOLLIN;
	if (epoll_ctl(_epollFd, EPOLL_CTL_MOD, fd, &ev) == -1)
		std::cerr << "Failed to modify socket to epoll." << std::endl;
}

EventType EventDemux::_getEventType(uint32_t events)
{
	EventType evType;

	if (events & EPOLLIN)
		evType = READ_EVENT;
	else if (events & EPOLLOUT)
		evType = WRITE_EVENT;
	return (evType);
}

uint32_t EventDemux::_getEventsMask(EventType eventType)
{
	uint32_t events;

	events = 0;
	if (eventType == READ_EVENT)
		events = EPOLLIN;
	if (eventType == WRITE_EVENT)
		events = EPOLLOUT;
	return (events);
}
