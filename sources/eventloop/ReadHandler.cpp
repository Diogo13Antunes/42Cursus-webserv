/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/23 14:19:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadHandler.hpp"

#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <string>


#include "HandleReq.hpp"
#include "HeaderProcess.hpp"
#include "HeaderGetData.hpp"


ReadHandler::ReadHandler(void) {}

ReadHandler::ReadHandler(ConfigsData data):
	IEventHandler(),
	_data(data)
{}

ReadHandler::ReadHandler(const ReadHandler &src) {}

ReadHandler::~ReadHandler(void) {}

/*
ReadHandler &ReadHandler::operator=(const ReadHandler &src)
{
	//ReadHandler Copy Assignment Operator
}
*/

void ReadHandler::handleEvent(Event *event)
{
	char			buffer[20];
	ssize_t			valread;
	RequestParser	parser;
	short			state;

	HandleReq		hadleReq(event);
	
	
	hadleReq.setState(HEADER_GET_DATA);
	std::cout << "-------------TESTE-----------" << std::endl;
	//while (hadleReq.handle());
	hadleReq.handle();
	std::cout << "-----------------------------" << std::endl;
	

	for(int i = 0; i < 20; i++)
		buffer[i] = 0;
	valread = read(event->getFd(), buffer, 20 - 1);


	if (event->getParseState() == HEADER_HANDLE || event->getParseState() == BODY_HANDLE)
		event->updateReqRaw(buffer);
	if (event->getParseState() == HEADER_DONE)
	{
		std::string str = event->getHeaderRaw();
		parser.headerParse(str);
		event->setResquestHeader(parser.getRequestLine(), parser.getRequestHeader());

		if (event->getBodySize())
			event->setParseState(BODY_HANDLE);
	}
	if (event->getParseState() == BODY_HANDLE)
	{
		if (event->isBodyComplete())
			event->setParseState(BODY_DONE);
	}
	if (event->getParseState() == BODY_DONE)
	{
		std::string str = event->getReqRaw();
		parser.bodyParse(str);
		event->setResquestBody(parser.getRequestBody());
	}
	if (event->getParseState() == BODY_DONE || (event->getParseState() == HEADER_DONE && !event->getBodySize()))
	{
		event->createResponse(_data);
		event->setState(WRITE_EVENT);
	}
}

EventType ReadHandler::getHandleType(void)
{
	return (READ_EVENT);
}
