/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/14 16:18:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(int dst, int fd, MessageType type):
	_dst(dst),

	_type(type)
{}

Message::~Message(void) {}

MessageType	Message::getType(void)
{
	return (_type);
}

int Message::getDst(void)
{
	return (_dst);
}

int Message::getFd(void)
{
	return (_fd);
}
