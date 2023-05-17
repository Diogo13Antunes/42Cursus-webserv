/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/17 19:05:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadHandler.hpp"

ReadHandler::ReadHandler(void)
{
	//Default ReadHandler Constructor
}

ReadHandler::ReadHandler(const ReadHandler &src)
{
	//ReadHandler Copy Constructor
}

ReadHandler::~ReadHandler(void)
{
	//Default ReadHandler Destructor
}

/*
ReadHandler &ReadHandler::operator=(const ReadHandler &src)
{
	//ReadHandler Copy Assignment Operator
}
*/

void ReadHandler::handleEvent(void)
{
	std::cout << "handle READ event" << std::endl; 
}

EventType ReadHandler::getHandleType(void)
{
	return (READ_EVENT);
}
