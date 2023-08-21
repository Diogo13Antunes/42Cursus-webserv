/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:47 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/16 12:16:50 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <sys/socket.h>

#include "WriteHandler.hpp"
#include "HandleRes.hpp"


WriteHandler::WriteHandler(HandleRes *handleRes): IEventHandler()
{
	_handleRes = handleRes;
}

WriteHandler::~WriteHandler(void) 
{
	if (_handleRes)
		delete _handleRes;
}

void WriteHandler::handleEvent(Event *event)
{
	/* if (event->getCgiBodyRes().size() > 0)
	{
		std::cout << event->getCgiBodyRes() << std::endl;
	} */
	_handleRes->setEvent(event);
	_handleRes->handle();
	if (_handleRes->isResProcessingComplete())
		event->setActualState(TYPE_TRANSITION);
}

EventType WriteHandler::getHandleType(void)
{
	return (WRITE_EVENT);
}