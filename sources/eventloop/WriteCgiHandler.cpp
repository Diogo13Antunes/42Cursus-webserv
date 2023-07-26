/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteCgiHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:39:35 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/26 17:34:09 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WriteCgiHandler.hpp"

WriteCgiHandler::WriteCgiHandler(void)
{

}

WriteCgiHandler::~WriteCgiHandler(void)
{

}

void WriteCgiHandler::handleEvent(Event *event)
{

	std::string str;
	int			nwrite;

	str = "Write to script from the std server\r\n";
	nwrite = event->writeToCgi(str);
	event->setActualState(TYPE_TRANSITION);
}

EventType WriteCgiHandler::getHandleType(void)
{
	return (WRITE_CGI);
}