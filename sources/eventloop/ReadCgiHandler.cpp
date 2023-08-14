/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadCgiHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:38:17 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/02 08:32:38 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadCgiHandler.hpp"

#include <iostream>

ReadCgiHandler::ReadCgiHandler(void)
{

}

ReadCgiHandler::~ReadCgiHandler(void)
{

}

void ReadCgiHandler::handleEvent(Event *event)
{
	std::string str;
	int			nRead;

	nRead = event->readFromCgi(str);
	if (nRead > 0)
		event->updateCgiScriptResult(str);
	else
		event->setActualState(TYPE_TRANSITION);

	//for(int i = 0; i < 99999999; i++);
	//std::cout << "CGI status code: " << event->isCgiScriptEnd() << std::endl;
}

EventType ReadCgiHandler::getHandleType(void)
{
	return (READ_CGI);
}