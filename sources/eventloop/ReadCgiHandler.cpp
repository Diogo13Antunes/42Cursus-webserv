/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadCgiHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:38:17 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/06 16:00:29 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadCgiHandler.hpp"
#include <iostream>

#define BUFFER_SIZE	50000

ReadCgiHandler::ReadCgiHandler(void) {}

ReadCgiHandler::~ReadCgiHandler(void) {}

void ReadCgiHandler::handleEvent(Event *event)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	nRead;
	std::string	dataRead;

	std::cout << "ReadCgiHandler" << std::endl;

	nRead = read(event->getCgiReadFd(), buffer, BUFFER_SIZE);
	if (nRead <= 0)
		event->setStatusCode(500);
	dataRead.assign(buffer, nRead);
	event->updateCgiScriptResult(dataRead);
}

EventType ReadCgiHandler::getHandleType(void)
{
	return (READ_CGI);
}
