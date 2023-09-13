/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseState.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:15:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/13 12:04:05 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseState.hpp"

#include <sys/socket.h>
#include <iostream>
#include <EventType.hpp>

ResponseState::ResponseState(void) {}

ResponseState::~ResponseState(void) {}

StateResType ResponseState::handle(Event *event, ServerConfig& config)
{
	ssize_t		numBytesSend;
	size_t		resSize;
	std::string	res;

	std::cout << "ResponseState" << std::endl;

	res = event->getRes();
	resSize = res.size();

	//std::cout << "--------------------" << std::endl;
	//std::cout << res << std::endl;

	numBytesSend = send(event->getFd(), res.c_str(), resSize, 0);

	std::cout << "numBytesSend: " << numBytesSend << std::endl;
	std::cout << "resSize: " << resSize << std::endl;
	if (numBytesSend <= 0)
	{
		event->setClientDisconnected();
		return (RESPONSE_END);
	}
	if (numBytesSend == resSize)
		event->clearRes();
	else
		event->eraseRes(0, numBytesSend);
	event->updateTotalBytesSend(numBytesSend);
	if (_isResponseFullySend(event->getTotalBytesSend(), event->getResSize()))
	{
		std::cout << "CHEGA AO FINAL" << std::endl;
		return (RESPONSE_END);
	}
	if (event->getFileSize())
		return (STATIC_FILE_HANDLING);
	return (RESPONSE);
}

bool ResponseState::_isResponseFullySend(size_t totalBytesSend, size_t resSize)
{
	if (totalBytesSend >= resSize)
		return (true);
	return (false);
}
