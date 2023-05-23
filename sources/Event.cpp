/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:31 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/22 17:56:17 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"

Event::Event(void)
{
	//Default Event Constructor
}

Event::Event(int fd, int state):
	_fd(fd),
	_state(state)
{}

Event::Event(const Event &src)
{
	//Event Copy Constructor
}

Event::~Event(void)
{
	//Default Event Destructor
}

/*
Event &Event::operator=(const Event &src)
{
	//Event Copy Assignment Operator
}
*/


int Event::getFd(void)
{
	return (_fd);
}

short Event::getState(void)
{
	return (_state);
}

void Event::setState(short state)
{
	_state = state;
}