/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadSocketHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/25 12:53:13 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadSocketHandler.hpp"
#include "HandleReq.hpp"
#include <unistd.h>
#include <string>
#include <sys/socket.h>

ReadSocketHandler::ReadSocketHandler(HandleReq *handleReq): IEventHandler()
{
	_handleReq = handleReq;
}

ReadSocketHandler::~ReadSocketHandler(void) 
{
	if (_handleReq)
		delete _handleReq;
}

void ReadSocketHandler::handleEvent(Event *event)
{
	std::string	buffer;
	std::string	reqData;
	ssize_t		valread;

	_handleReq->setEvent(event);
	valread = recv(event->getFd(), _buffer, SOCKET_READ_BUFF_SIZE, 0);
	if (valread <= 0)
	{
		event->setActualState(DISCONNECT_EVENT);
		event->setClientDisconnected();
		return ;
	}
	buffer.assign(_buffer, valread);
	event->updateReqRawData(buffer);
	if (_isHttps(event))
		event->setActualState(DISCONNECT_EVENT);
	else
		_handleReq->handle();
	if (_handleReq->isProcessingComplete())
	{
		if (event->isCgi() && !event->getStatusCode())
			event->setActualState(WRITE_CGI);
		else
			event->setActualState(WRITE_SOCKET);
	}
}

EventType ReadSocketHandler::getHandleType(void)
{
	return (READ_SOCKET);
}

// SSL/TLS handshake starts with byte 0x16
bool ReadSocketHandler::_isHttps(Event *event)
{
	std::string reqData = event->getReqRawData();

	if (!reqData.empty() && !event->isHttpsTested())
	{
		event->setHttpsTested();
		if (reqData.at(0) == 0x16)
			return (true);
	}
	return (false);
}
