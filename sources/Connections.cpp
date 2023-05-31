/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/31 12:18:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

/*
Connections::Connections(Messenger *messenger):
	_messenger(messenger)
{}
*/

Connections::Connections(void): AMessengerClient(NULL)
{}

Connections::~Connections(void)
{
	_removeAllConnections();
}

/*
void Connections::updateAllConnections(void)
{
	//t_msg msg;

	//msg.dst = EVENTDEMUX_ID;
	//msg.type = 1;
	for (int i = 0; i < _activeConnects.size(); i++)
	{
		if (_activeConnects.at(i)->isKeepAliveTimeout())
		{
			//msg.fd = _activeConnects.at(i)->getFd();
			//sendMessage(msg);
			//_removeConnection(i);
			i--;
		}
	}
}
*/

void Connections::updateAllConnections(void)
{
	std::map<int, Connection *>::iterator it;

	it = _activeConnects.begin();
	while (it != _activeConnects.end())
	{
		if (it->second->isKeepAliveTimeout())
		{
			sendMessage(new ConnectionMessage(EVENTDEMUX_ID, it->second->getFd()));
			_removeConnection(it);
			break;
		}
		it++;
	}
}

ClientID Connections::getId(void)
{
	return (CONNECTIONS_ID);
}

void Connections::receiveMessage(Message *msg)
{
	std::map<int, Connection *>::iterator	it;
	ConnectionMessage						*m;
	int										fd;

	m = dynamic_cast<ConnectionMessage*>(msg);
	if (!m)
		return ;
	fd = m->getFd();
	it = _activeConnects.find(m->getFd());
	if (it == _activeConnects.end())
		_activeConnects.insert(std::make_pair(fd, new Connection(fd)));
	else
		it->second->resetKeepAliveTimeout();
}

// Just for debug (remove when not necessary)
// Remove
void Connections::showConnections(void)
{
	std::map<int, Connection *>::iterator it;

	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++)
		it->second->showDataConnection();
}

void Connections::_removeAllConnections(void)
{
	std::map<int, Connection *>::iterator it;

	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++)
		_removeConnection(it);
}

void Connections::_removeConnection(std::map<int, Connection *>::iterator it)
{
	delete it->second;
	_activeConnects.erase(it);
}
