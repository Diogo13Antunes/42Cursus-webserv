/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteCgiHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:39:35 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/27 16:37:11 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WriteCgiHandler.hpp"

WriteCgiHandler::WriteCgiHandler(void)
{

}

WriteCgiHandler::~WriteCgiHandler(void)
{

}

void WriteCgiHandler::handleEvent(Event *event)
{
	const char*	bodyStr;
	size_t		bodySize;
	size_t		sentChars;
	int			nwrite;

	bodyStr = event->getReqBody().c_str();
	bodySize = event->getReqBody().size();
	sentChars = event->getCgiSentChars();
	if (sentChars < bodySize)
	{
		bodyStr += sentChars;
		nwrite = event->writeToCgi(bodyStr);
		// Se falhar tem de ser mandado um 501 Internal Server Error
		event->updateCgiSentChars(nwrite);
	}
	else
	{
		event->writeToCgi("\n");
		event->setActualState(TYPE_TRANSITION);
	}
}

EventType WriteCgiHandler::getHandleType(void)
{
	return (WRITE_CGI);
}
