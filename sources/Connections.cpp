/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/11 16:05:10 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

Connections::Connections(void) {}

Connections::~Connections(void)
{
	_removeAllConnections();
}

int Connections::getNumConnections(void)
{
	return (_activeConnects.size());
}

struct pollfd Connections::getServerConnection(void)
{
	return (_fds[0]);
}

void Connections::addNewConnection(int fd, short events)
{
	size_t numConns;
	
	_activeConnects.push_back(new Connection(fd, events, 0));
	numConns = _activeConnects.size();
	_fds[numConns - 1] = _activeConnects.at(numConns - 1)->getFd();
}

void Connections::addNewConnection(int fd, short events, short revents)
{
	size_t numConns;

	_activeConnects.push_back(new Connection(fd, events, revents));
	numConns = _activeConnects.size();
	_fds[numConns - 1] = _activeConnects.at(numConns - 1)->getFd();
}

struct pollfd *Connections::getConnectionsArray(void)
{
	Connection *conn;

	for (int i = 0; i < _activeConnects.size(); i++)
	{
		conn = _activeConnects.at(i);
		if (i > 0 && _isConnectionTimeout(conn->getLastRequestTime(),
			conn->getKeepAliveTimeout()))
		{
			_removeConnection(i);
			std::cout << "remove connection" << std::endl;
			i--;
		}
		else
			_fds[i] = _activeConnects.at(i)->getFd();		
	}
	return _fds;
}


// Just for debug and tests
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
		_activeConnects.at(i)->setPollFd(_fds[i]);
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

bool Connections::_isConnectionTimeout(time_t startTime, int timeout)
{
	int		elapsedTime;

	elapsedTime = (int)(time(NULL) - startTime);
	if (elapsedTime >= timeout)
		return (true);
	return (false);
}