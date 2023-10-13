/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteSocketHandler.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:47 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/21 11:57:39 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <sys/socket.h>

#include "WriteSocketHandler.hpp"
#include "HandleRes.hpp"

WriteSocketHandler::WriteSocketHandler(HandleRes *handleRes): IEventHandler()
{
	_handleRes = handleRes;
}

WriteSocketHandler::~WriteSocketHandler(void) 
{
	if (_handleRes)
		delete _handleRes;
}

void WriteSocketHandler::handleEvent(Event *event)
{
	_handleRes->setEvent(event);
	_handleRes->handle();
	if (_handleRes->isResProcessingComplete())
	{
		if (event->isConnectionClose())
			event->setActualState(DISCONNECT_EVENT);
		else 
			event->setActualState(CLOSE_EVENT);
	}
}

EventType WriteSocketHandler::getHandleType(void)
{
	return (WRITE_SOCKET);
}