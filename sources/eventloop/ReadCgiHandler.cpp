/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadCgiHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:38:17 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/27 15:50:48 by dsilveri         ###   ########.fr       */
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
	
	//for(int i = 0; i < 99999999; i++);
	//std::cout << "CGI status code: " << event->isCgiScriptEnd() << std::endl;

	//event->setActualState(TYPE_TRANSITION);
}

EventType ReadCgiHandler::getHandleType(void)
{
	return (READ_CGI);
}