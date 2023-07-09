/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/09 18:28:45 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

Connections::Connections(void): AMessengerClient(NULL) {}

Connections::~Connections(void)
{
	_removeAllConnections();
}

void Connections::updateAllConnections(void)
{
	std::map<int, Connection *>::iterator it;

	it = _activeConnects.begin();
	while (it != _activeConnects.end())
	{
		if (it->second->isKeepAliveTimeout())
		{
			sendMessage(new ConnectionMessage(EVENTDEMUX_ID, it->second->getFd(), CLOSE_CONNECTION));
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
	ConnectionMessage	*m;

	m = dynamic_cast<ConnectionMessage*>(msg);
	if (!m)
		return ;
	_handleMessage(m);
}

// Just for debug (remove when not necessary)
// Remove
void Connections::showConnections(void)
{
	std::map<int, Connection *>::iterator it;

	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++)
		it->second->showDataConnection();
}

void Connections::_handleMessage(ConnectionMessage *msg)
{
	std::map<int, Connection *>::iterator	it;
	int										fd;

	fd = msg->getFd();
	it = _activeConnects.find(fd);
	if (it == _activeConnects.end())
		_activeConnects.insert(std::make_pair(fd, new Connection(fd)));
	else
	{
		it->second->resetKeepAliveTimeout();
		if (msg->getState() == PROCESSING)
			it->second->setProcessingState();
		else if (msg->getState() == PAUSED)
			it->second->setWaitingState();
		else if (msg->getState() == CLOSE_CONNECTION)
		{
			std::cout << "DEVE REMOVER O EVENTO EVENTDEMUX"  << std::endl;

			sendMessage(new ConnectionMessage(EVENTDEMUX_ID, it->second->getFd(), CLOSE_CONNECTION));
			_removeConnection(it);
		}
	}
	
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
