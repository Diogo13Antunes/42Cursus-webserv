/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messenger.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:11:39 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 21:26:30 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Messenger.hpp"

#include <iostream>

Messenger::Messenger(void) {}

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
