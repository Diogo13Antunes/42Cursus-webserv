/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 10:42:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(void) {}

Message::Message(int dst): _dst(dst) {}

Message::Message(const Message &src) {}

Message::~Message(void) {}

/*
Message &Message::operator=(const Message &src)
{
	//IMessage Copy Assignment Operator
}
*/

int Message::getDst(void)
{
	return (_dst);
}
