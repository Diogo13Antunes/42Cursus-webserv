/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:47 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/18 12:09:03 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WriteHandler.hpp"

WriteHandler::WriteHandler(void)
{
	//Default WriteHandler Constructor
}

WriteHandler::WriteHandler(const WriteHandler &src)
{
	//WriteHandler Copy Constructor
}

WriteHandler::~WriteHandler(void)
{
	//Default WriteHandler Destructor
}

/*
WriteHandler &WriteHandler::operator=(const WriteHandler &src)
{
	//WriteHandler Copy Assignment Operator
}
*/

void WriteHandler::handleEvent(int event)
{
	std::cout << "handle WRITE event" << event << std::endl;
}

EventType WriteHandler::getHandleType(void)
{
	return (WRITE_EVENT);
}
