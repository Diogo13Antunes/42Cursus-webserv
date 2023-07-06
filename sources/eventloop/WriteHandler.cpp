/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:47 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/06 15:38:44 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <sys/socket.h>

#include "WriteHandler.hpp"
#include "HandleRes.hpp"

WriteHandler::WriteHandler(void): IEventHandler()
{
	_handleRes = NULL;
}

WriteHandler::WriteHandler(HandleRes *handleRes): IEventHandler()
{
	_handleRes = handleRes;
}

WriteHandler::WriteHandler(const WriteHandler &src) {}

WriteHandler::~WriteHandler(void) 
{
	if (_handleRes)
		delete _handleRes;
}

/*
WriteHandler &WriteHandler::operator=(const WriteHandler &src)
{
	//WriteHandler Copy Assignment Operator
}
*/

void WriteHandler::handleEvent(Event *event)
{
	_handleRes->setEvent(event);
	_handleRes->handle();
	if (_handleRes->isResProcessingComplete())
		event->setState(COMPLETE_EVENT);
}

EventType WriteHandler::getHandleType(void)
{
	return (WRITE_EVENT);
}