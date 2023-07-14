/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/14 16:17:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>

#include "Connection.hpp"
#include "AMessengerClient.hpp"

class Connections: public AMessengerClient
{
	private:
		std::map<int, Connection *> _activeConnects;

		Connection *	_getConnection(int fd);
		void			_removeAllConnections(void);
		void			_removeConnection(std::map<int, Connection *>::iterator it);
		void 			_removeConnection(int fd);
		void			_addNewConnection(int fd);
		void			_pauseKeepAliveTimer(int fd);
		void			_restartKeepAliveTimer(int fd);
		void			_resetKeepAliveTimer(int fd);

	public:
		Connections(void);
		Connections(Messenger *messenger);
		~Connections(void);

		void		updateAllConnections(void);
		ClientID	getId(void);
		void		receiveMessage(Message *msg);

		// for debug only
		void			showConnections(void);
	
};
