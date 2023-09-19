/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteCgiHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:39:35 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/19 09:49:22 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WriteCgiHandler.hpp"
#include <unistd.h>

WriteCgiHandler::WriteCgiHandler(void) {}

WriteCgiHandler::~WriteCgiHandler(void) {}


void WriteCgiHandler::handleEvent(Event *event)
{
	const char*	bodyStr;
	size_t		bodySize;
	ssize_t		numBytesSend;
	int			fd;
	
	bodyStr = event->getReqBody().c_str();
	bodySize = event->getReqBody().size();
	numBytesSend = event->getNumBytesSendCgi();
	fd = event->getCgiWriteFd();
	if (numBytesSend < bodySize && bodySize)
	{
		bodyStr += numBytesSend;
		numBytesSend = write(fd, bodyStr, bodySize - numBytesSend);
		event->updateNumBytesSendCgi(numBytesSend);
		if (event->getNumBytesSendCgi() >= bodySize)
		{
			write(fd, "\n", 1);
			event->setIsStateChange(true);
			event->setActualState(READ_CGI);
		}
	}
	else
	{
		event->setIsStateChange(true);
		event->setActualState(READ_CGI);
	}
}

EventType WriteCgiHandler::getHandleType(void)
{
	return (WRITE_CGI);
}
