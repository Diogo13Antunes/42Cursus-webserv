/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/10 11:40:55 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

Connection::Connection(int fd, short events, short revents):
	_keepAliveTimeout(40), 
	_lastRequestTime(time(NULL)),
	_isServerFd(false)
{
	_fd.fd = fd;
	_fd.events = events;
	_fd.revents = revents;

	std::cout << "new Conection " << _fd.fd << std::endl;
}

/*
Connection::Connection(const Connection &src)
{

}
*/

Connection::~Connection(void)
{
	std::cout << "close conection " << _fd.fd << std::endl;
	close(_fd.fd);
}

/*
Connection &Connection::operator=(const Connection &src)
{

}
*/


void Connection::setAsServer(void)
{
	_isServerFd = true;
}

bool Connection::isServer(void)
{
	return (_isServerFd);
}

struct pollfd Connection::getFd(void)
{
	return (_fd);
}

void Connection::updateConnection(struct pollfd conn)
{
	_fd = conn;
}


int Connection::getKeepAliveTimeout(void)
{
	return(_keepAliveTimeout);
}

time_t Connection::getLastRequestTime(void)
{
	return(_lastRequestTime);
}

void Connection::setLastRequestTime(time_t time)
{
	_lastRequestTime = time;
}

// Just for debug (remove when not necessary)
// Remove
void Connection::showDataConnection(void)
{
	std::cout << "------------ Connection ------------" << std::endl;
	std::cout << "fd: " << _fd.fd << std::endl;
	std::cout << "is server: " << isServer() << std::endl;
	std::cout << "revents: " << _fd.revents << std::endl;
	std::cout << "events: " << _fd.events << std::endl;
	std::cout << "keep-alive: " << _keepAliveTimeout << std::endl;
	std::cout << "last request: " << _lastRequestTime << std::endl;
}