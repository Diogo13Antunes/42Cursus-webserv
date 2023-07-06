/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/31 17:04:03 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>

#include "Connection.hpp"
#include "AMessengerClient.hpp"
#include "ConnectionMessage.hpp"

class Connections: public AMessengerClient
{
	private:
		std::map<int, Connection *> _activeConnects;

		void	_handleMessage(ConnectionMessage *msg);
		void	_removeAllConnections(void);
		void	_removeConnection(std::map<int, Connection *>::iterator it);

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
