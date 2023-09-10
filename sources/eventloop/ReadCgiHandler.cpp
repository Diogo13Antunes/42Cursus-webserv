/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadCgiHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:38:17 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/10 15:09:16 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadCgiHandler.hpp"
#include <iostream>

#define BUFFER_SIZE	50000

ReadCgiHandler::ReadCgiHandler(void) {}

ReadCgiHandler::~ReadCgiHandler(void) {}

void ReadCgiHandler::handleEvent(Event *event)
{
	ssize_t		nRead;
	std::string	dataRead;

	nRead = read(event->getCgiReadFd(), _buffer, BUFFER_CGI_READ_SIZE);
	if (nRead <= 0)
		event->setStatusCode(500);
	dataRead.assign(_buffer, nRead);
	event->updateCgiScriptResult(dataRead);
}

EventType ReadCgiHandler::getHandleType(void)
{
	return (READ_CGI);
}
