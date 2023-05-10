/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/10 11:37:21 by dsilveri         ###   ########.fr       */
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
	removeAllConnections();
}

/*
Connections &Connections::operator=(const Connections &src)
{

}
*/

void Connections::addNewConnection(int fd, short events)
{
	size_t numConns;
	
	std::cout << "connection Added" << std::endl;
		
	_activeConnects.push_back(new Connection(fd, events, 0));
	numConns = _activeConnects.size();
	_fds[numConns - 1] = _activeConnects.at(numConns - 1)->getFd();
	if (numConns == 1)
		_activeConnects.front()->setAsServer();
}

void Connections::addNewConnection(int fd, short events, short revents)
{
	size_t numConns;

	std::cout << "connection Added" << std::endl;
	
	_activeConnects.push_back(new Connection(fd, events, revents));
	numConns = _activeConnects.size();
	_fds[numConns - 1] = _activeConnects.at(numConns - 1)->getFd();
	if (numConns == 1)
		_activeConnects.front()->setAsServer();
}

void Connections::removeConnection()
{
	std::cout << "connection remove" << std::endl;
}

struct pollfd *Connections::getConnectionsArray(void)
{
	std::vector<Connection *>::iterator	begin;
	int									index;
	int									timeout;
	int									pastTime;
	time_t								lastRequestTime;
	int									i;

	begin = _activeConnects.begin();

	i = 0;
	while(i < _activeConnects.size())
	{
		lastRequestTime = _activeConnects.at(i)->getLastRequestTime();
		timeout = _activeConnects.at(i)->getKeepAliveTimeout();
		pastTime = (int) (time(NULL) - lastRequestTime);
		
		/*if (i > 0)
		{
			std::cout << "time: " << pastTime << std::endl;
		}*/

		if (i > 0 && pastTime >= timeout)
		{
			delete _activeConnects.at(i);
			_activeConnects.erase(begin + i);
		}
		else
		{
			_fds[i] = _activeConnects.at(i)->getFd();
			i++;
		}
	}

/*
	std::cout << "#############################" << std::endl;
	std::cout << "size: " << _activeConnects.size() << std::endl;
	showConnections();
*/
	
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
	send(socket_fd, res.c_str(), res.size(), 0);
}

void Connections::updateConnections(void)
{
	char	buffer[30000];
	ssize_t	valread;
	size_t	numConns;

	numConns = _activeConnects.size();

	// Just for test and debug
	for(int i = 0; i < 30000; i++)
		buffer[i] = 0;

	for (int i = 0; i < numConns; i++)
	{
		_activeConnects.at(i)->updateConnection(_fds[i]);
		if (_activeConnects.at(i)->getFd().revents == POLLIN)
			_activeConnects.at(i)->setLastRequestTime(time(NULL));

		// Just for test and debug
		if (i > 0 && _activeConnects.at(i)->getFd().revents == POLLIN)
		{
			valread = read(_activeConnects.at(i)->getFd().fd , buffer, 30000 - 1);
			std::cout << buffer << std::endl;
			send_response_test(_activeConnects.at(i)->getFd().fd);
			showConnections();
		}
	}
}

/*
struct pollfd* Connections::getConnections(void)
{
	return (_fds);
}
*/

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
