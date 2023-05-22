/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messenger.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:11:39 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/22 11:35:23 by dsilveri         ###   ########.fr       */
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
