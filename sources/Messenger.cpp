/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messenger.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:11:39 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/27 15:11:16 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Messenger.hpp"

Messenger::Messenger(void)
{
	//Default Messenger Constructor
}

Messenger::Messenger(const Messenger &src)
{
	//Messenger Copy Constructor
}

Messenger::~Messenger(void)
{
	//Default Messenger Destructor
}

/*
Messenger &Messenger::operator=(const Messenger &src)
{
	//Messenger Copy Assignment Operator
}
*/

/*
void Messenger::registerModule(IModule *module)
{
	ModuleID id;

	id = module->getId();
	msgHandler.insert(std::pair<ModuleID, IModule*>(id, module));
}

void Messenger::unregisterModule(IModule *module)
{
	msgHandler.erase(module->getId());
}

void Messenger::sendMessage(t_msg msg)
{
	std::map<ModuleID, IModule*>::iterator it;

	if (msgHandler.size())
	{
		it = msgHandler.find(msg.dst);
		it->second->handleMessage(msg);
	}
}
*/

void Messenger::registerclient(AMessengerClient *client)
{
	ClientID id;

	id = client->getId();
	_clients.insert(std::pair<ClientID, AMessengerClient*>(id, client));
}

void Messenger::unregisterclient(AMessengerClient *client)
{
	_clients.erase(client->getId());
}

void Messenger::sendMessage(t_msg msg)
{
	std::map<ClientID, AMessengerClient*>::iterator it;

	if (_clients.size())
	{
		it = _clients.find(msg.dst);
		it->second->receiveMessage(msg);
	}
}
