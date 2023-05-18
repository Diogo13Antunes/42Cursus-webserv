/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/18 15:38:49 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

Connections::Connections(void)
{

}

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



// Just for debug and tests
/*
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
*/

void Connections::updateConnections(void)
{
	//char	buffer[30000];
	//ssize_t	valread;
	size_t	numConns;

	numConns = _activeConnects.size();

	// Just for test and debug
	//for(int i = 0; i < 30000; i++)
	//	buffer[i] = 0;

	for (int i = 0; i < numConns; i++)
	{
		_activeConnects.at(i)->setPollFd(_pollFds[i]);
		if (_activeConnects.at(i)->getPollFd().revents == POLLIN)
			_activeConnects.at(i)->setLastRequestTime(time(NULL));

		// Just for test and debug
		/*if (i > 0 && _activeConnects.at(i)->getPollFd().revents == POLLIN)
		{
			valread = read(_activeConnects.at(i)->getPollFd().fd , buffer, 30000 - 1);
			std::cout << buffer << std::endl;
			send_response_test(_activeConnects.at(i)->getPollFd().fd);
			showConnections();
		}*/
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
