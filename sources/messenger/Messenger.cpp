/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messenger.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:11:39 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/15 11:55:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Messenger.hpp"

#include <iostream>

Messenger::Messenger(void) {}

Messenger::Messenger(const Messenger &src) {}

Messenger::~Messenger(void) {}

void Messenger::registerClient(AMessengerClient *client)
{
	ClientID id;

	id = client->getId();
	_clients.insert(std::pair<ClientID, AMessengerClient*>(id, client));
}

void Messenger::unregisterClient(ClientID clientID)
{
	_clients.erase(clientID);
}

void Messenger::sendMessage(Message msg)
{
	std::map<ClientID, AMessengerClient*>::iterator it;

	if (_clients.size())
	{
		it = _clients.find((ClientID) msg.getDst());
		if (it != _clients.end())
			it->second->receiveMessage(msg);
	}
}
