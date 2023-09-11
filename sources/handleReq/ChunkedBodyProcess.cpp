/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkedBodyProcess.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:19:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 08:41:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChunkedBodyProcess.hpp"
#include <iostream>

ChunkedBodyProcess::ChunkedBodyProcess(void) {}

ChunkedBodyProcess::~ChunkedBodyProcess(void) {}

StateReqType ChunkedBodyProcess::handle(Event *event, ConfigsData *configsData)
{
	std::string	bodyChunked = event->getReqRaw1();
	size_t				index;
	int					bodySize;
	std::string			body;
	int					totalSize;

	while (true)
	{
		index = bodyChunked.find("0\r\n\r\n");
		if (index == 0)
			return (REQUEST_END);
		index = bodyChunked.find("\r\n");
		if (index == bodyChunked.npos)
			return (CHUNKED_BODY_PROCESS);
		bodySize = _hexToDec(bodyChunked.substr(0, index));
		if (bodySize == 0)
			return (CHUNKED_BODY_PROCESS);
		index += 2;
		totalSize = index + bodySize + 2;
		if (totalSize >= bodyChunked.size())
			return (CHUNKED_BODY_PROCESS);
		event->updateReqBody(bodyChunked.substr(index, bodySize));
		event->setReqRaw1(bodyChunked.substr(totalSize));
		bodyChunked = bodyChunked.substr(totalSize);
	}
	return (REQUEST_END);
}

int ChunkedBodyProcess::_hexToDec(std::string hex)
{
	std::stringstream	ss;
	int					res;

	ss << std::hex << hex;
	ss >> res;
	return (res);
}
