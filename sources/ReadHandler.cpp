/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/26 11:13:05 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadHandler.hpp"

#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

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

void ReadHandler::handleEvent(Event *event)
{
	char	buffer[90000];
	ssize_t	valread;

	for(int i = 0; i < 90000; i++)
		buffer[i] = 0;

	valread = read(event->getFd(), buffer, 90000 - 1);

	std::cout << buffer << std::endl;
	std::cout << "handle READ event: " << event->getFd() << std::endl;
}

EventType ReadHandler::getHandleType(void)
{
	return (READ_EVENT);
}
