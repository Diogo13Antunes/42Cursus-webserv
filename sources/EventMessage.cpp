/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:49:27 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/29 15:31:29 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventMessage.hpp"

EventMessage::EventMessage(void)
{
	//Default EventMessage Constructor
}

EventMessage::EventMessage(ClientID dst, int fd, short event):
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

EventMessage &EventMessage::operator=(const EventMessage &src)
{
	//EventMessage Copy Assignment Operator
}

int EventMessage::getFd(void)
{
	return (_fd);
}

short EventMessage::getEvent(void)
{
	return (_event);
}
