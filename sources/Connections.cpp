/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/08 14:55:03 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"


/**
 * Public Methods
*/

Connections::Connections(void)
{
	
}

/*
Connections::Connections(const Connections &src)
{

}
*/

Connections::~Connections(void)
{
	this->removeAllConnections();
}

/*
Connections &Connections::operator=(const Connections &src)
{

}
*/

void Connections::addNewConnection(int fd, short events)
{
	std::cout << "connection Added" << std::endl;
		
	_activeConnects.push_back(new Connection(fd, events));
	if (_activeConnects.size() == 1)
		_activeConnects.front()->setAsServer();
}

void Connections::removeConnection()
{
	std::cout << "connection remove" << std::endl;
}

struct pollfd *Connections::getConnectionsArray(void)
{
	std::vector<Connection *>::iterator	it;
	int									index;

	index = 0;
	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++, index++)
		_fds[index] = (*it)->getFd();
	return _fds;
}

int Connections::getNumConnections(void)
{
	return (_activeConnects.size());
}


// Just for debug (remove when not necessary)
// Remove
void Connections::showConnections(void)
{
	std::vector<Connection *>::iterator it;

	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++)
		(*it)->showDataConnection();
}


/**
 * Private Methods
*/
	
void Connections::removeAllConnections(void)
{
	std::vector<Connection *>::iterator it;

	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++)
		delete *it;
}
