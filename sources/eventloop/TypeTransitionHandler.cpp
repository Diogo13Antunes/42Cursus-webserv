/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTransitionHandler.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:00:53 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/25 18:38:15 by dsilveri         ###   ########.fr       */
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

	if (event->getOldState() == READ_EVENT)
	{
		if (!event->getReqLinePath().compare(CGI_PATH))
		{
			std::cout << "TypeTransitionHandler: CGI" << std::endl;
			event->setActualState(WRITE_CGI);
		}
		else
			event->setActualState(WRITE_EVENT);
	}
	if (event->getOldState() == WRITE_EVENT)
	{
		event->setAsFinished();
		event->setActualState(READ_EVENT);
	}
}

EventType TypeTransitionHandler::getHandleType(void)
{
	return (TYPE_TRANSITION);
}