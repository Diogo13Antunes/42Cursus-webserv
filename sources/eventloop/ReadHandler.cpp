/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/03 09:14:58 by dsilveri         ###   ########.fr       */
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
	valread = read(event->getFd(), _buffer, BUFF_SIZE1);
	if (valread <= 0)
	{
		event->setClientDisconnected();
		return ;
	}
	buff.assign(_buffer, valread);
	event->updateReqRaw1(buff);
	_handleReq->handle();
	if (!_handleReq->isProcessingComplete())
		return ;

	std::cout << event->getReqBody() << std::endl;

	event->setActualState(TYPE_TRANSITION);
}

EventType ReadHandler::getHandleType(void)
{
	return (READ_EVENT);
}