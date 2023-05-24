/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/24 17:43:38 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <sys/socket.h>
#include <sys/poll.h>
#include "Connection.hpp"
#include "Event.hpp"
#include "IModule.hpp"
#include "Messenger.hpp"

class Connections: public IModule
{
	private:
		std::vector<Connection *>	_activeConnects;
		struct pollfd				_pollFds[1024];
		int							_index;
		Messenger					*_messenger;

		void	_sendMessage(t_msg msg);

		void	_removeAllConnections(void);
		void	_removeConnection(int index);

	public:
		Connections(void);
		Connections(Messenger *messenger);
		~Connections(void);

		struct pollfd	*getPollFds(void);
		int 			getNumOfConnections(void);
		struct pollfd	getServerConnection(void);

		void			addNewConnection(Connection *conn);
		void			removeExpiredConnections(void);
		void			updateConnections(void);

		// new
		void			updateAllConnections(void);

		ModuleID		getId(void);
		void			handleMessage(t_msg msg);

		// for debug only
		void			showConnections(void);
	
};
