/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/30 11:38:15 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
//#include <vector>
#include <map>

#include <sys/socket.h>
#include <sys/poll.h>
#include "Connection.hpp"
#include "Event.hpp"
//#include "Messenger.hpp"
#include "AMessengerClient.hpp"

#include "ConnectionMessage.hpp"
#include "EventMessage.hpp"

class Connections: public AMessengerClient
{
	private:
		std::map<int, Connection *> _activeConnects;

		//std::vector<Connection *>	_activeConnects;


		//Messenger					*_messenger;

		//void	_sendMessage(t_msg msg);

		void	_removeAllConnections(void);
		void	_removeConnection(std::map<int, Connection *>::iterator it);
		//void	_removeConnection(int index);

	public:
		Connections(void);
		Connections(Messenger *messenger);
		~Connections(void);

		// new
		void			updateAllConnections(void);


		ClientID	getId(void);
		void		receiveMessage(Message *msg);

		// for debug only
		void			showConnections(void);
	
};
