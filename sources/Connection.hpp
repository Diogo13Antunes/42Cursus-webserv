/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:28 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/11 17:20:43 by dsilveri         ###   ########.fr       */
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
		struct pollfd	_pollFd;
		int				_keepAliveTimeout;
		time_t			_lastRequestTime;

	public:

		Connection(int fd, short events, short revents);
		~Connection(void);

		struct pollfd	getPollFd(void);
		int				getKeepAliveTimeout(void);
		time_t			getLastRequestTime(void);
		void			setLastRequestTime(time_t lastRequestTime);
		void			setPollFd(struct pollfd pollFd);

		bool			isKeepAliveTimeout(void);

		// Just for debug
		void			showDataConnection(void);
};
