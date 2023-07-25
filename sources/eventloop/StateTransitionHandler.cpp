/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateTransitionHandler.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:00:53 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/25 12:05:09 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StateTransitionHandler.hpp"
#include "iostream"

StateTransitionHandler::StateTransitionHandler(void) {}


StateTransitionHandler::~StateTransitionHandler(void) {}

void StateTransitionHandler::handleEvent(Event *event)
{
	//std::cout << "StateTransitionHandler" << std::endl;

	if (event->getOldState() == READ_EVENT)
		event->setActualState(WRITE_EVENT);
	if (event->getOldState() == WRITE_EVENT)
	{
		event->setAsFinished();
		event->setActualState(READ_EVENT);
	}
}

EventType StateTransitionHandler::getHandleType(void)
{
	return (STATE_TRANSITION);
}