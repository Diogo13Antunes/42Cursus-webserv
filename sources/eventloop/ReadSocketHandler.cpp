/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadSocketHandler.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/15 14:42:49 by dsilveri         ###   ########.fr       */
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
		event->setClientDisconnected();
		return ;
	}
	buffer.assign(_buffer, valread);
	event->updateReqRawData(buffer);
	_handleReq->handle();
	//if (!_handleReq->isProcessingComplete())
	//	return ;
	//event->setActualState(TYPE_TRANSITION);
	if (_handleReq->isProcessingComplete())
	{
		event->setIsStateChange(true);
		event->setActualState(WRITE_EVENT);
	}
}

EventType ReadSocketHandler::getHandleType(void)
{
	return (READ_SOCKET);
}
