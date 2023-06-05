/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:28 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 10:12:10 by dsilveri         ###   ########.fr       */
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
		int				_fd;
		int				_keepAliveTimeout;
		time_t			_lastRequestTime;

	public:
		Connection(int fd);
		~Connection(void);

		int				getFd(void);
		bool			isKeepAliveTimeout(void);
		void			resetKeepAliveTimeout(void);

		// Just for debug
		void			showDataConnection(void);
};
