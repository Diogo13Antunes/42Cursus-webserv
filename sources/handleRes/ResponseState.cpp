/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseState.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:15:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/16 17:09:40 by dcandeia         ###   ########.fr       */
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

	res = event->getRes();
	resSize = res.size();
	numBytesSend = send(event->getFd(), res.c_str(), resSize, 0);
	if (numBytesSend <= 0)
	{
		//event->setState(CLOSED_EVENT);
		event->setClientDisconnected();
		return (RESPONSE_END);
	}
	
	std::cout << "RES_SIZE: " << resSize << std::endl;
	std::cout << "BYTES_SEND: " << numBytesSend << std::endl;
	
	if (numBytesSend >= resSize)
	{
		std::cout << "AQUI" << std::endl;
		//std::cout << event->getRes() << std::endl;
		// numBytesSend = send(event->getFd(), res.c_str(), resSize, 0);
		event->setRes("");
	}
	else
		event->setRes(res.substr(numBytesSend));
	event->updateTotalBytesSend(numBytesSend);

	/* if (_isResponseFullySend(event->getTotalBytesSend(), event->getResSize()))
	{
		std::cout << "RESPONSE_END" << std::endl;
		return (RESPONSE_END);
	} */
	return (GET_BODY);
}

bool ResponseState::_isResponseFullySend(size_t totalBytesSend, size_t resSize)
{
	if (totalBytesSend >= resSize)
		return (true);
	return (false);
}
