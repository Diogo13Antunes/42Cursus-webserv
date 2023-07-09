/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/08 15:50:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadHandler.hpp"

#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <string>


#include "HandleReq.hpp"


#define BUFF_SIZE 100000


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
	char			buffer[BUFF_SIZE];
	ssize_t			valread;

	//std::cout << "read event ReadHandler: " << event->getFd() << std::endl;

	_handleReq->setEvent(event);
	for(int i = 0; i < BUFF_SIZE; i++)
		buffer[i] = 0;
	valread = read(event->getFd(), buffer, BUFF_SIZE - 1);

	event->updateReqRaw1(buffer);
	_handleReq->handle();
	if (!_handleReq->isProcessingComplete())
		return ;
	event->setState(WRITE_EVENT);
}

EventType ReadHandler::getHandleType(void)
{
	return (READ_EVENT);
}