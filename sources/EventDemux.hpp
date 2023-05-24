/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventDemux.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:09:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/24 16:15:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "IModule.hpp"
#include "Messenger.hpp"

#define N_MAX_EVENTS	1024

class EventDemux: public IModule
{
	private:
		struct epoll_event	_events[N_MAX_EVENTS];
		int					_serverFd;
		int					_epollFd;
		socklen_t			_addrlen;
		struct sockaddr_in	_address;
		Messenger			*_messenger;

		void	_addNewFdToEventList(int fd);
		void	_sendMessage(t_msg msg);
		
	public:
		EventDemux(void);
		EventDemux(Messenger *messenger);
		EventDemux(int serverFd, struct sockaddr_in address, socklen_t addrlen);
		EventDemux(const EventDemux &src);
		~EventDemux(void);
		EventDemux &operator=(const EventDemux &src);

		void		setServerFd(int serverFd);
		void		setMessenger(Messenger *messenger);

		void		waitAndDispatchEvents(void);

		ModuleID	getId(void);
		void		handleMessage(t_msg msg);
};
