/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:47 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/18 12:03:02 by dsilveri         ###   ########.fr       */
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
	_handleRes->setEvent(event);
	_handleRes->handle();
	if (_handleRes->isResProcessingComplete())
	{
		event->setIsStateChange(true);
		if (event->isConnectionClose())
			event->setActualState(DISCONNECT_EVENT);
		else 
			event->setActualState(CLOSE_EVENT);
	}
}

EventType WriteHandler::getHandleType(void)
{
	return (WRITE_EVENT);
}