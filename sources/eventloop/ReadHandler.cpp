/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/23 14:40:06 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadHandler.hpp"

#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <string>


#include "HandleReq.hpp"


//#define BUFF_SIZE 100000


ReadHandler::ReadHandler(void): IEventHandler()
{
	_handleReq = NULL;
}

ReadHandler::ReadHandler(HandleReq *handleReq): IEventHandler()
{
	_handleReq = handleReq;
}

ReadHandler::ReadHandler(const ReadHandler &src) {}

ReadHandler::~ReadHandler(void) 
{
	if (_handleReq)
		delete _handleReq;
}

/*
ReadHandler &ReadHandler::operator=(const ReadHandler &src)
{
	//ReadHandler Copy Assignment Operator
}
*/

void ReadHandler::handleEvent(Event *event)
{
	ssize_t		valread;
	std::string	buff;	

	_handleReq->setEvent(event);
	valread = read(event->getFd(), _buffer, BUFF_SIZE1 - 1);
	if (valread == 0 || valread == -1)
	{
		//std::cout << "FECHOU O NAVEGADOR: " << valread << std::endl;
		event->setState(CLOSED_EVENT);
		event->setClientClosed();
		return ;
	}
	buff.assign(_buffer, valread);
	event->updateReqRaw1(buff);
	_handleReq->handle();
	if (!_handleReq->isProcessingComplete())
		return ;
	if (event->getCgiFlag())
	{
		std::cout << "Coloca CGI STATE" << std::endl;
		event->setState(CGI_EVENT);
	}
	else
		event->setActualState(STATE_TRANSITION);//event->setState(READ_EVENT_COMPLETE);//event->setState(WRITE_EVENT);
}

EventType ReadHandler::getHandleType(void)
{
	return (READ_EVENT);
}