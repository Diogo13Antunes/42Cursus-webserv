/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionMessage.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:49:50 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/09 11:23:17 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionMessage.hpp"

ConnectionMessage::ConnectionMessage(void): Message() {}

ConnectionMessage::ConnectionMessage(int dst, int fd, ConnectionAction state):
	Message(dst),
	_fd(fd),
	_state(state)
{}

ConnectionMessage::ConnectionMessage(const ConnectionMessage &src) {}

ConnectionMessage::~ConnectionMessage(void) {}

/*
ConnectionMessage &ConnectionMessage::operator=(const ConnectionMessage &src)
{
	//ConnectionMessage Copy Assignment Operator
}
*/

int	ConnectionMessage::getFd(void)
{
	return (_fd);
}

ConnectionAction ConnectionMessage::getState(void)
{
	return (_state);
}
