/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventDemux.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:09:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 12:39:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "AMessengerClient.hpp"
#include "ConnectionMessage.hpp"
#include "EventMessage.hpp"
#include "EventType.hpp"

#define N_MAX_EVENTS	1024

/*
typedef enum 
{
    READ = 0,
    WRITE
}	Type;
*/

class EventDemux: public AMessengerClient
{
	private:
		struct epoll_event	_events[N_MAX_EVENTS];
		int					_serverFd;
		int					_epollFd;
		socklen_t			_addrlen;
		struct sockaddr_in	_address;

		void		_addNewEvent(int fd);
		void		_removeEvent(int fd);
		void		_changeEvent(int fd, EventType eventType);
		EventType	_getEventType(uint32_t events);
		uint32_t	_getEventsMask(EventType eventType);
		bool		_existEvent(int fd);
		
	public:
		EventDemux(void);
		EventDemux(int serverFd, struct sockaddr_in address, socklen_t addrlen);
		EventDemux(const EventDemux &src);
		~EventDemux(void);
		EventDemux &operator=(const EventDemux &src);

		void		waitAndDispatchEvents(void);
		ClientID	getId(void);
		void		receiveMessage(Message *msg);
};
