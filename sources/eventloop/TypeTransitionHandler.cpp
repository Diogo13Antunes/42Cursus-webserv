/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTransitionHandler.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:00:53 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 14:31:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TypeTransitionHandler.hpp"
#include "iostream"

#define CGI_PATH "/cgi"

TypeTransitionHandler::TypeTransitionHandler(void) {}

TypeTransitionHandler::~TypeTransitionHandler(void) {}

void TypeTransitionHandler::handleEvent(Event *event)
{
	//std::cout << "StateTransitionHandler" << std::endl;

	if (event->getOldState() == READ_SOCKET)
	{
		if (!event->getReqLinePath().compare(CGI_PATH))
		{
			//std::cout << "TypeTransitionHandler: CGI" << std::endl;
			event->setActualState(WRITE_CGI);
		}
		else
			event->setActualState(WRITE_EVENT);
	}
	else if (event->getOldState() == WRITE_EVENT)
	{
		event->setAsFinished();
		event->setActualState(READ_SOCKET);
	}
	else if (event->getOldState() == WRITE_CGI)
	{
		if (event->getCgiExitStatus() != NO_EXIT_STATUS)
			event->setActualState(WRITE_EVENT);
		else
			event->setActualState(READ_CGI);
	}
	else if (event->getOldState() == READ_CGI)
		event->setActualState(WRITE_EVENT);
}

EventType TypeTransitionHandler::getHandleType(void)
{
	return (TYPE_TRANSITION);
}
