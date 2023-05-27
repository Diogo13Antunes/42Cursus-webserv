/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/27 11:11:58 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

Connections::Connections(Messenger *messenger):
	_messenger(messenger),
	_index(1)
{}

Connections::~Connections(void)
{
	_removeAllConnections();
}

void Connections::updateAllConnections(void)
{
	t_msg msg;

	msg.dst = EVENTDEMUX_ID;
	msg.type = 1;
	for (int i = 0; i < _activeConnects.size(); i++)
	{
		if (_activeConnects.at(i)->isKeepAliveTimeout())
		{
			msg.fd = _activeConnects.at(i)->getFd();
			_sendMessage(msg);
			_removeConnection(i);
			i--;
		}
	}
}

ModuleID Connections::getId(void)
{
	return (CONNECTIONS_ID);
}

void Connections::handleMessage(t_msg msg)
{

	std::cout << "Connections receive mensage: fd: " << msg.fd << std::endl;

	if (msg.fd > 0 && msg.type == 0)
		_activeConnects.push_back(new Connection(msg.fd));
	else if (msg.type == 1)
	{
		std::cout << "update the connection timeout" << std::endl;
		for (int i = 0; i < _activeConnects.size(); i++)
		{
			if (_activeConnects.at(i)->getFd() == msg.fd)
				_activeConnects.at(i)->resetKeepAliveTimeout();
		}
	}
}

// Just for debug (remove when not necessary)
// Remove
void Connections::showConnections(void)
{
	std::vector<Connection *>::iterator it;

	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++)
		(*it)->showDataConnection();
}

void	Connections::_sendMessage(t_msg msg)
{
	_messenger->sendMessage(msg);
}

void Connections::_removeAllConnections(void)
{
	std::vector<Connection *>::iterator it;

	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++)
		delete *it;
}

void Connections::_removeConnection(int index)
{
	std::vector<Connection *>::iterator	begin;

	begin = _activeConnects.begin();
	delete _activeConnects.at(index);
	_activeConnects.erase(begin + index);
}
