/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadCgiHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:38:17 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/25 18:02:12 by dsilveri         ###   ########.fr       */
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
	std::cout << "ReadCgiHandler" << std::endl;
}

EventType ReadCgiHandler::getHandleType(void)
{
	return (READ_CGI);
}