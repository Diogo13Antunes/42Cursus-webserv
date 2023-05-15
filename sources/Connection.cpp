/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/15 13:48:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

Connection::Connection(int fd, short events, short revents):
	_keepAliveTimeout(60), 
	_lastRequestTime(time(NULL))
{
	_pollFd.fd = fd;
	_pollFd.events = events;
	_pollFd.revents = revents;
}

Connection::~Connection(void)
{
	std::cout << "remove connection" << std::endl;
	close(_pollFd.fd);
}

struct pollfd Connection::getPollFd(void)
{
	return (_pollFd);
}

int Connection::getKeepAliveTimeout(void)
{
	return(_keepAliveTimeout);
}

time_t Connection::getLastRequestTime(void)
{
	return(_lastRequestTime);
}

void Connection::setLastRequestTime(time_t lastRequestTime)
{
	_lastRequestTime = lastRequestTime;
}

void Connection::setPollFd(struct pollfd pollFd)
{
	_pollFd = pollFd;
}

bool Connection::isKeepAliveTimeout(void)
{
	int		elapsedTime;

	elapsedTime = (int)(time(NULL) - _lastRequestTime);
	if (elapsedTime >= _keepAliveTimeout)
		return (true);
	return (false);
}

// Just for debug (remove when not necessary)
// Remove
void Connection::showDataConnection(void)
{
	std::cout << "------------ Connection ------------" << std::endl;
	std::cout << "fd: " << _pollFd.fd << std::endl;
	std::cout << "revents: " << _pollFd.revents << std::endl;
	std::cout << "events: " << _pollFd.events << std::endl;
	std::cout << "keep-alive: " << _keepAliveTimeout << std::endl;
	std::cout << "last request: " << _lastRequestTime << std::endl;
}
