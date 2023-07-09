/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/09 17:50:39 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"
#include "Timer.hpp"

Connection::Connection(int fd):
	_fd(fd),
	_keepAliveTimeout(15),
	_lastRequestTime(Timer::getActualTimeStamp()),
	_status(WAITING_EVENTS)
{}

Connection::~Connection(void)
{
	std::cout << "remove connection: " << _fd << std::endl;
	close(_fd);
}

int Connection::getFd(void)
{
	return (_fd);
}

bool Connection::isKeepAliveTimeout(void)
{
	if (_status == PROCESSING_EVENTS)
		resetKeepAliveTimeout();
	return (Timer::isTimeoutExpired(_lastRequestTime, _keepAliveTimeout));
}

void Connection::resetKeepAliveTimeout(void)
{
	_lastRequestTime = time(NULL);
}

void Connection::setProcessingState(void)
{
	_status = PROCESSING_EVENTS;
}

void Connection::setWaitingState(void)
{
	_status = WAITING_EVENTS;
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
