/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/07 09:45:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"


Connection::Connection(int fd):
	_fd(fd),
	_keepAliveTimeout(100), 
	_lastRequestTime(time(NULL))
{}

Connection::~Connection(void)
{
	std::cout << "remove connection" << std::endl;
	close(_fd);
}

int Connection::getFd(void)
{
	return (_fd);
}

bool Connection::isKeepAliveTimeout(void)
{
	int		elapsedTime;

	elapsedTime = (int)(time(NULL) - _lastRequestTime);
	if (elapsedTime >= _keepAliveTimeout)
		return (true);
	return (false);
}

void Connection::resetKeepAliveTimeout(void)
{
	_lastRequestTime = time(NULL);
}


// Just for debug (remove when not necessary)
// Remove
void Connection::showDataConnection(void)
{
	std::cout << "------------ Connection ------------" << std::endl;
	std::cout << "fd: " << _fd << std::endl;
	std::cout << "keep-alive: " << _keepAliveTimeout << std::endl;
	std::cout << "last request: " << _lastRequestTime << std::endl;
}
