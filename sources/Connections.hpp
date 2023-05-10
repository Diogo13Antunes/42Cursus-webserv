/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/10 11:08:09 by dsilveri         ###   ########.fr       */
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
		void 						removeAllConnections(void);
		void 						removeConnection(void);

	public:
		Connections(void);
		//Connections(const Connections &src);
		~Connections(void);

		//Connections		&operator=(const Connections &src);

		int 			getNumConnections(void);
		struct pollfd	getServerConnection(void);
		struct pollfd 	*getConnections(void);
		struct pollfd	*getConnectionsArray(void);
		
		


		void			addNewConnection(int fd, short events);
		void			addNewConnection(int fd, short events, short revents);
		

		void			updateConnections(void);

		// for debug only
		void			showConnections(void);
	
};
