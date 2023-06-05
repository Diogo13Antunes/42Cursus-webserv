/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:49:27 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 10:53:16 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventMessage.hpp"

EventMessage::EventMessage(void): Message() {}

EventMessage::EventMessage(int dst, int fd, short event):
	Message(dst),
	_fd(fd),
	_event(event)
{}

EventMessage::EventMessage(const EventMessage &src) {}

EventMessage::~EventMessage(void) {}

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
