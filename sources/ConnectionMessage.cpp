/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionMessage.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:49:50 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/29 15:58:07 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectionMessage.hpp"

ConnectionMessage::ConnectionMessage(void)
{
	//Default ConnectionMessage Constructor
}

ConnectionMessage::ConnectionMessage(ClientID dst, int fd):
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

ConnectionMessage &ConnectionMessage::operator=(const ConnectionMessage &src)
{
	//ConnectionMessage Copy Assignment Operator
}

int	ConnectionMessage::getFd(void)
{
	return (_fd);
}