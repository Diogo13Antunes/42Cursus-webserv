/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadSocketHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/21 11:57:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadSocketHandler.hpp"
#include "HandleReq.hpp"
#include <unistd.h>
#include <string>

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
	ssize_t		valread;

	_handleReq->setEvent(event);
	valread = read(event->getFd(), _buffer, SOCKET_READ_BUFF_SIZE);
	if (valread <= 0)
	{
		event->setActualState(DISCONNECT_EVENT);
		event->setClientDisconnected();
		return ;
	}
	buffer.assign(_buffer, valread);
	event->updateReqRawData(buffer);
	_handleReq->handle();
	if (_handleReq->isProcessingComplete())
	{
		if (event->isCgi())
			event->setActualState(WRITE_CGI);
		else
			event->setActualState(WRITE_SOCKET);
	}
}

EventType ReadSocketHandler::getHandleType(void)
{
	return (READ_SOCKET);
}
