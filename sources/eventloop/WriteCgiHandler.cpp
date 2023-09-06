/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteCgiHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:39:35 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/06 15:43:15 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WriteCgiHandler.hpp"

WriteCgiHandler::WriteCgiHandler(void) {}

WriteCgiHandler::~WriteCgiHandler(void) {}

void WriteCgiHandler::handleEvent(Event *event)
{
	const char*	bodyStr;
	int			bodySize;
	ssize_t		numBytesSend;
	ssize_t		numBytesSent;

	std::cout << "WriteCgiHandler" << std::endl;

	bodyStr = event->getReqBody().c_str();
	bodySize = event->getReqBody().size();
	numBytesSent = event->getNumBytesSendCgi();
	if (numBytesSent < numBytesSend)
		bodyStr += numBytesSent;
	numBytesSend = write(event->getCgiWriteFd(), bodyStr, bodySize - numBytesSent);

	std::cout << "numBytesSend: " << numBytesSend << std::endl;

	if (numBytesSend == -1 || numBytesSend == 0)
	{
		event->setActualState(TYPE_TRANSITION);
		event->setStatusCode(500);
		event->closeCgiWriteFd();
	}
	event->updateNumBytesSendCgi(numBytesSend);
	if (event->getNumBytesSendCgi() >= bodySize)
	{
		event->setActualState(TYPE_TRANSITION);
		event->closeCgiWriteFd();
	}
}

/*
void WriteCgiHandler::handleEvent(Event *event)
{
	const char*	bodyStr;
	size_t		bodySize;
	size_t		sentChars;
	int			nwrite;


	std::cout << "WriteCgiHandler" << std::endl;

	bodyStr = event->getReqBody().c_str();
	bodySize = event->getReqBody().size();

	sentChars = event->getCgiSentChars();	
	if (sentChars < bodySize)
	{
		bodyStr += sentChars;
		nwrite = event->writeToCgi(bodyStr, bodySize - sentChars);

		// Se falhar tem de ser mandado um 500 Internal Server Error
		event->updateCgiSentChars(nwrite);

		if (event->getCgiSentChars() >= bodySize)
		{
			// event->writeToCgi("\n");
			close(event->getCgiWriteFd());
			event->setActualState(TYPE_TRANSITION);
		}
	}
	else
	{
		// event->writeToCgi("\n");
		close(event->getCgiWriteFd());
		event->setActualState(TYPE_TRANSITION);
	}
}
*/

/*
void WriteCgiHandler::handleEvent(Event *event)
{
	const char*	bodyStr;
	size_t		bodySize;
	size_t		sentChars;
	int			nwrite;

	bodyStr = event->getReqBody().c_str();
	bodySize = event->getReqBody().size();

	std::cout << "bodySize: " << bodySize << std::endl;

	sentChars = event->getCgiSentChars();	
	if (sentChars < bodySize)
	{
		bodyStr += sentChars;
		nwrite = event->writeToCgi(bodyStr);

		// Se falhar tem de ser mandado um 501 Internal Server Error
		event->updateCgiSentChars(nwrite);
		if (event->getCgiSentChars() >= bodySize)
		{
			// event->writeToCgi("\n");
			close(event->getCgiWriteFd());
			event->setActualState(TYPE_TRANSITION);
		}
	}
	else
	{
		// event->writeToCgi("\n");
		close(event->getCgiWriteFd());
		event->setActualState(TYPE_TRANSITION);
	}
}
*/

EventType WriteCgiHandler::getHandleType(void)
{
	return (WRITE_CGI);
}
