/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/15 13:52:15 by dsilveri         ###   ########.fr       */
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
		struct pollfd				_pollFds[1024];

		void 						_removeAllConnections(void);
		void 						_removeConnection(int index);

	public:
		Connections(void);
		~Connections(void);

		struct pollfd	*getPollFds(void);
		int 			getNumOfConnections(void);
		struct pollfd	getServerConnection(void);

		void			addNewConnection(Connection *conn);
		void			removeExpiredConnections(void);
		void			updateConnections(void);

		// for debug only
		void			showConnections(void);
	
};
