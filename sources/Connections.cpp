/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/22 11:56:20 by dsilveri         ###   ########.fr       */
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

	numConns = _activeConnects.size();
	for (int i = 1; i < numConns; i++)
	{
		_activeConnects.at(i)->setPollFd(_pollFds[i]);
		if (_activeConnects.at(i)->getPollFd().revents == POLLIN)
		{
			_activeConnects.at(i)->setLastRequestTime(time(NULL));
			msg.dst = EVENTLOOP_ID;
			msg.fd = _activeConnects.at(i)->getFd();
			_sendMessage(msg);
		}
	}
}

/*
Event* Connections::getNextEvent(void)
{
	int size;

	size =  _activeConnects.size();
	if (size <= 1)
		return (NULL);
	while (_index < size)
	{
		if (_pollFds[_index].revents)
		{
			_activeConnects.at(_index)->setPollFd(_pollFds[_index]);
			return (new Event(_activeConnects.at(_index++)));
		}
		_index++;
	}
	_index = 1;
	return (NULL);
}
*/

ModuleID Connections::getId(void)
{
	return (CONNECTIONS_ID);
}

void Connections::handleMessage(t_msg msg)
{
	//std::cout << "Menssage reived by Connections: msg: " << msg.msg << std::endl;
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
