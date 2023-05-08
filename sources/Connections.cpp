/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/08 19:17:58 by dsilveri         ###   ########.fr       */
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
		
	_activeConnects.push_back(new Connection(fd, events, 0));
	if (_activeConnects.size() == 1)
		_activeConnects.front()->setAsServer();
}

void Connections::addNewConnection(int fd, short events, short revents)
{
	std::cout << "connection Added" << std::endl;
		
	_activeConnects.push_back(new Connection(fd, events, revents));
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

struct pollfd Connections::getServerConnection(void)
{
	return (_fds[0]);
}


void send_response_test(int socket_fd)
{
	std::string head;
	std::string body;
	std::string res;

	std::stringstream out;

	body = "<html><head><title>WebServer</title></head><body><h1>Hello World</h1></body></html>\r\n\r\n";
	out << body.size();
	
	head = "HTTP/1.1 200 OK\r\nContent-length: ";
	head += out.str();
	head += "\r\n";
	head += "Content-Type: text/html\r\n\r\n";
	res = head + body;

	//std::cout << "#################" << std::endl; 
	//std::cout << head << std::endl; 

	send(socket_fd, res.c_str(), res.size(), 0);
}


void Connections::updateConnections(void)
{
	char buffer[30000];
	ssize_t valread;

	//std::cout << "porra chega aqui ou não " << std::endl;

	for (int i = 0; i < _activeConnects.size(); i++)
	{
		if (i < _activeConnects.size() - 1)
			_activeConnects.at(i)->updateConnection(_fds[i]);

		if (i > 0 && _activeConnects.at(i)->getFd().revents == POLLIN)
		{
			valread = read(_activeConnects.at(i)->getFd().fd , buffer, 30000);
			std::cout << buffer << std::endl;
			send_response_test(_activeConnects.at(i)->getFd().fd);

			showConnections();
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


/**
 * Private Methods
*/
	
void Connections::removeAllConnections(void)
{
	std::vector<Connection *>::iterator it;

	for(it = _activeConnects.begin(); it != _activeConnects.end(); it++)
		delete *it;
}
