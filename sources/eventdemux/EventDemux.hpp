/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventDemux.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:09:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/16 12:16:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#include "AMessengerClient.hpp"

#define N_MAX_EVENTS	100000

class EventDemux: public AMessengerClient
{
	private:
		struct epoll_event	_events[N_MAX_EVENTS];
		int					_serverFd;
		int					_epollFd;
		socklen_t			_addrlen;
		struct sockaddr_in	_address;

		void	_addNewEvent(int fd);
		void	_removeEvent(int fd);
		void	_changeEvent(int fd, uint32_t eventMask);
		bool	_isReadEvent(uint32_t eventMask);
		bool	_isWriteEvent(uint32_t eventMask);

	public:
		EventDemux(void);
		EventDemux(int serverFd, struct sockaddr_in address, socklen_t addrlen);
		~EventDemux(void);

		void		waitAndDispatchEvents(void);
		ClientID	getId(void);
		void		receiveMessage(Message *msg);
};
