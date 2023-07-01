/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseState.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:15:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/01 16:07:50 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseState.hpp"
#include <sys/socket.h>

#include <iostream>

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

	//std::cout << "ResponseState" << std::endl;

	//std::cout << "size: " << event->getRes().size() << std::endl;
	//std::cout << event->getRes() << std::endl;

	res = event->getRes();
	resSize = res.size();
	numBytesSend = send(event->getFd(), res.c_str(), resSize, 0);
	//std::cout << "------" << std::endl;
	//std::cout << "numBytesSend: " << numBytesSend << std::endl;
	//std::cout << "------" << std::endl;
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

