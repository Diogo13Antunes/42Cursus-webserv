/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:28 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/08 14:52:44 by dsilveri         ###   ########.fr       */
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
		struct pollfd	_fd;
		bool			_isServerFd;
		int				_keepAliveTimeout;
		clock_t			_lastRequestTicks;

	public:
		//struct pollfd _fd;
		Connection(int fd, short events);
		//Connection(const Connection &src);
		~Connection(void);
		//Connection &operator=(const Connection &src);

		void setAsServer(void);
		bool isServer(void);
		struct pollfd getFd(void);
		

		void showDataConnection(void);
};
