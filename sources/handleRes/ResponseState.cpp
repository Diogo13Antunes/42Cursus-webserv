/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseState.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:15:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/14 16:19:57 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseState.hpp"

#include <sys/socket.h>
#include <iostream>
#include <EventType.hpp>

ResponseState::ResponseState(void)
{
	//Default ResponseState Constructor
}

ResponseState::ResponseState(const ResponseState &src)
{
	//ResponseState Copy Constructor
}

ResponseState::~ResponseState(void)
{
	//Default ResponseState Destructor
}

/*
ResponseState &ResponseState::operator=(const ResponseState &src)
{
	//ResponseState Copy Assignment Operator
}
*/


StateResType ResponseState::handle(Event *event, ConfigsData confiagsDta)
{
	ssize_t		numBytesSend;
	size_t		resSize;
	std::string	res;
	size_t		size = 1000; 

	res = event->getRes();
	resSize = res.size();
	numBytesSend = send(event->getFd(), res.c_str(), resSize, 0);
	if (numBytesSend <= 0)
	{
		//event->setState(CLOSED_EVENT);
		event->setClientDisconnected();
		return (RESPONSE_END);
	}
	if (numBytesSend >= resSize)
		event->setRes("");
	else
		event->setRes(res.substr(numBytesSend));
	event->updateTotalBytesSend(numBytesSend);

	if (_isResponseFullySend(event->getTotalBytesSend(), event->getResSize()))
		return (RESPONSE_END);
	return (GET_BODY);
}

bool ResponseState::_isResponseFullySend(size_t totalBytesSend, size_t resSize)
{
	if (totalBytesSend >= resSize)
		return (true);
	return (false);
}
