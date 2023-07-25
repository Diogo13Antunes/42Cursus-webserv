/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:47 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/25 12:33:59 by dsilveri         ###   ########.fr       */
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
	//std::cout << "Evento de escrita: " << event->getFd() << std::endl;

	// Terminal::printMessages("--------------------------------");
	// std::cout << event->getCgiScriptResult() << std::endl;
	// Terminal::printMessages("--------------------------------");

	_handleRes->setEvent(event);
	_handleRes->handle();
	if (_handleRes->isResProcessingComplete())
		event->setActualState(STATE_TRANSITION);
	//if (_handleRes->isResProcessingComplete())
	//	event->setState(WRITE_EVENT_COMPLETE);
}

EventType WriteHandler::getHandleType(void)
{
	return (WRITE_EVENT);
}