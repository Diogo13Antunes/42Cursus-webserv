/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/11 15:51:59 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <sys/poll.h>
#include <ctime>
#include "Connection.hpp"

class Connections
{
	private:
		std::vector<Connection *>	_activeConnects;
		struct pollfd				_fds[1024];

		void 						_removeAllConnections(void);
		void 						_removeConnection(int index);
		bool 						_isConnectionTimeout(time_t startTime, int timeout);

	public:
		Connections(void);
		~Connections(void);

		int 			getNumConnections(void);
		struct pollfd	getServerConnection(void);
		struct pollfd	*getConnectionsArray(void);
		
	

		void			addNewConnection(int fd, short events);
		void			addNewConnection(int fd, short events, short revents);
		

		void			updateConnections(void);

		// for debug only
		void			showConnections(void);
	
};
