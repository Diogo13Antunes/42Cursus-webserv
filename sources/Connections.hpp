/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/08 18:41:49 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <sys/poll.h>
#include "Connection.hpp"

class Connections
{
	private:
		std::vector<Connection *>	_activeConnects;
		

		void removeAllConnections(void);
		void removeConnection(void);

	public:

		struct pollfd				_fds[1024];
		
		Connections(void);
		//Connections(const Connections &src);
		~Connections(void);
		//Connections &operator=(const Connections &src);

		void addNewConnection(int fd, short events);
		void addNewConnection(int fd, short events, short revents);
		struct pollfd *getConnectionsArray(void);
		int getNumConnections(void);
		struct pollfd getServerConnection(void);

		void updateConnections(void);

		// for debug only
		void showConnections(void);
};
