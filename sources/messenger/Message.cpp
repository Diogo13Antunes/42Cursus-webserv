/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/15 11:51:51 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(int dst, int fd, MessageType type):
	_dst(dst),
	_fd(fd),
	_type(type)
{}

Message::Message(const Message& other):
	_dst(other.getDst()),
	_fd(other.getFd()),
	_type(other.getType())
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
