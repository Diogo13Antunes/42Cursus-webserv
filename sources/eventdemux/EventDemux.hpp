/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventDemux.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:09:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/15 11:29:16 by dsilveri         ###   ########.fr       */
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
#include "configs.hpp"

class EventDemux: public AMessengerClient
{
	private:
		struct epoll_event					_events[EPOLL_MAX_NEVENTS];
		int									_epollFd;
		std::map<int, struct sockaddr_in>	_servers;

		void	_addNewEvent(int fd);
		void	_removeEvent(int fd);
		void	_changeEvent(int fd, uint32_t eventMask);
		bool	_isReadEvent(uint32_t eventMask);
		bool	_isWriteEvent(uint32_t eventMask);
		int		_acceptClientConnectionIfServer(int fd);

	public:
		EventDemux(void);
		~EventDemux(void);

		void		init(std::map<int, struct sockaddr_in> servers);
		void		waitAndDispatchEvents(void);
		ClientID	getId(void);
		void		receiveMessage(Message msg);
};
