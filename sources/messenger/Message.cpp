/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 21:20:25 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(int dst, int fd, MessageType type):
	_type(type),
	_dst(dst),
	_fd(fd)
{}

Message::Message(const Message& other):
	_type(other.getType()),
	_dst(other.getDst()),
	_fd(other.getFd())
{}

Message::~Message(void) {}

Message& Message::operator=(const Message& other)
{
	if (this != &other)
	{
		this->_dst = other.getDst();
		this->_fd = other.getFd();
		this->_type = other.getType();
	}
	return (*this);
}

MessageType	Message::getType(void) const
{
	return (_type);
}

int Message::getDst(void) const
{
	return (_dst);
}

int Message::getFd(void) const
{
	return (_fd);
}
