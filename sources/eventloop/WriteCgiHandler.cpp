/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteCgiHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:39:35 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/26 11:31:48 by dsilveri         ###   ########.fr       */
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
	std::cout << "WriteCgiHandler" << std::endl;
}

EventType WriteCgiHandler::getHandleType(void)
{
	return (WRITE_CGI);
}