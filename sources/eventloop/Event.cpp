/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:31 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/09 10:49:44 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"

Event::Event(void) {}

Event::Event(int fd, int state):
	_fd(fd),
	_state(state)
{}

Event::Event(const Event &src) {}

Event::~Event(void) {}

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

std::string	Event::getResponse(void)
{
	return (_res);
}

void Event::setState(short state)
{
	_state = state;
}

void Event::setResponse(std::string res)
{
	_res = res;
}