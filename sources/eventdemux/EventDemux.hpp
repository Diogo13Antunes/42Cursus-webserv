/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventDemux.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:09:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/10 16:26:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <map>

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

		std::map<int, struct sockaddr_in>	_servers;


		void	_addNewEvent(int fd);
		void	_removeEvent(int fd);
		void	_changeEvent(int fd, uint32_t eventMask);
		bool	_isReadEvent(uint32_t eventMask);
		bool	_isWriteEvent(uint32_t eventMask);
		int		_acceptClientConnectionIfServer(int fd);

	public:
		EventDemux(void);
		EventDemux(int serverFd, struct sockaddr_in address, socklen_t addrlen);
		EventDemux(std::map<int, struct sockaddr_in> servers);
		~EventDemux(void);

		void		init(std::map<int, struct sockaddr_in> servers);
		void		waitAndDispatchEvents(void);
		ClientID	getId(void);
		void		receiveMessage(Message *msg);
};
