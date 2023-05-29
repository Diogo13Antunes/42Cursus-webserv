/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/29 17:27:29 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message(void)
{
	//Default IMessage Constructor
}

Message::Message(int dst):
	_dst(dst)
{}

Message::Message(const Message &src)
{
	//IMessage Copy Constructor
}

Message::~Message(void)
{
	//Default IMessage Destructor
}

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
