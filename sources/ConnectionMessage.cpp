/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionMessage.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:49:50 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/30 09:01:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionMessage.hpp"

ConnectionMessage::ConnectionMessage(void)
{
	//Default ConnectionMessage Constructor
}

ConnectionMessage::ConnectionMessage(int dst, int fd):
	Message(dst),
	_fd(fd)
{}

ConnectionMessage::ConnectionMessage(const ConnectionMessage &src)
{
	//ConnectionMessage Copy Constructor
}

ConnectionMessage::~ConnectionMessage(void)
{
	//Default ConnectionMessage Destructor
}

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