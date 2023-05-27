/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:28 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/27 10:26:13 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <unistd.h>
#include <sys/poll.h>
#include <ctime>

class Connection
{
	private:
		struct pollfd	_pollFd; // to remove
		int				_fd;
		int				_keepAliveTimeout;
		time_t			_lastRequestTime;

	public:

		Connection(int fd);

		// to remove events and revents is not necessary
		Connection(int fd, short events, short revents);
		~Connection(void);

		struct pollfd	getPollFd(void);
		int				getFd(void);
		short			getRevents(void);
		short			getEvents(void);
		int				getKeepAliveTimeout(void);
		time_t			getLastRequestTime(void);

		void			setLastRequestTime(time_t lastRequestTime);
		void			setPollFd(struct pollfd pollFd);
		void			setRevents(short revents);
		void			setEvents(short events);

		bool			isKeepAliveTimeout(void);
		void			resetKeepAliveTimeout(void);

		// Just for debug
		void			showDataConnection(void);
};
