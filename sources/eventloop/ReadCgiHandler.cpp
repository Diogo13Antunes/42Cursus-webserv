/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadCgiHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:38:17 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/16 11:52:51 by dcandeia         ###   ########.fr       */
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
}

EventType ReadCgiHandler::getHandleType(void)
{
	return (READ_CGI);
}