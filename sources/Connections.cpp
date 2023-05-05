/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/05 16:25:09 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

//
//	Public Methods
//

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

void Connections::addConnection(Connection *c)
{
	std::cout << "connection Added" << std::endl;

	this->activeConnects.push_back(c);
}

void Connections::removeConnection()
{
	std::cout << "connection remove" << std::endl;
}

// for debug only
void Connections::showConnections(void)
{
	std::vector<Connection *>::iterator it;

	for(it = this->activeConnects.begin(); it != this->activeConnects.end(); it++)
		std::cout << "fd: " << (*it)->_fd.fd << std::endl;
}

//
//	Private Methods
//

void Connections::removeAllConnections(void)
{
	std::vector<Connection *>::iterator it;

	for(it = this->activeConnects.begin(); it != this->activeConnects.end(); it++)
		delete *it;
}