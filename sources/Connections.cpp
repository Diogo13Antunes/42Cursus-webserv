/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/23 10:26:21 by dsilveri         ###   ########.fr       */
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

struct pollfd*	Connections::getPollFds(void)
{
	return (_pollFds);
}

int Connections::getNumOfConnections(void)
{
	return (_activeConnects.size());
}

struct pollfd Connections::getServerConnection(void)
{
	return (_pollFds[0]);
}

void Connections::addNewConnection(Connection *conn)
{
	size_t numConns;
	
	_activeConnects.push_back(conn);
	numConns = _activeConnects.size();
	_pollFds[numConns - 1] = _activeConnects.at(numConns - 1)->getPollFd();
}

void Connections::removeExpiredConnections(void)
{
	for (int i = 0; i < _activeConnects.size(); i++)
	{
		if (i > 0 && _activeConnects.at(i)->isKeepAliveTimeout())
		{
			_removeConnection(i);
			i--;
		}
		else
			_pollFds[i] = _activeConnects.at(i)->getPollFd();
	}
}

void Connections::updateConnections(void)
{
	size_t	numConns;
	t_msg	msg;
	short	revents;

	numConns = _activeConnects.size();
	msg.dst = EVENTLOOP_ID;
	for (int i = 0; i < numConns; i++)
	{
		_activeConnects.at(i)->setPollFd(_pollFds[i]);
		revents = _activeConnects.at(i)->getRevents();
		if (i > 0 && revents)
		{
			_activeConnects.at(i)->setLastRequestTime(time(NULL));
			msg.fd = _activeConnects.at(i)->getFd();
			msg.event = revents;
			_sendMessage(msg);
		}
	}
}

ModuleID Connections::getId(void)
{
	return (CONNECTIONS_ID);
}

void Connections::handleMessage(t_msg msg)
{
	std::vector<Connection *>::iterator it;
	
	//std::cout << "Menssage reived by Connections: msg: " << msg.fd << std::endl;
	
	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++)
	{
		if ((*it)->getFd() == msg.fd)
			(*it)->setEvents(msg.event);
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
