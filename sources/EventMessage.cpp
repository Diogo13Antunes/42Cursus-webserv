/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:49:27 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/30 09:01:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventMessage.hpp"

EventMessage::EventMessage(void)
{
	//Default EventMessage Constructor
}

EventMessage::EventMessage(int dst, int fd, short event):
	Message(dst),
	_fd(fd),
	_event(event)
{}

EventMessage::EventMessage(const EventMessage &src)
{
	//EventMessage Copy Constructor
}

EventMessage::~EventMessage(void)
{
	//Default EventMessage Destructor
}

/*
EventMessage &EventMessage::operator=(const EventMessage &src)
{
	//EventMessage Copy Assignment Operator
}
*/

int EventMessage::getFd(void)
{
	return (_fd);
}

short EventMessage::getEvent(void)
{
	return (_event);
}
