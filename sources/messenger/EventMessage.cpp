/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:49:27 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/11 16:12:47 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventMessage.hpp"

EventMessage::EventMessage(void): Message() {}

EventMessage::EventMessage(int dst, int fd, short event, EventAction action):
	Message(dst),
	_fd(fd),
	_event(event),
	_action(action)
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

EventAction	EventMessage::getAction(void)
{
	return (_action);
}