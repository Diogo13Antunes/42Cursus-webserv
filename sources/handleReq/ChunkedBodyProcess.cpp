/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkedBodyProcess.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:19:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/02 17:36:14 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChunkedBodyProcess.hpp"
#include <iostream>

ChunkedBodyProcess::ChunkedBodyProcess(void) {}

ChunkedBodyProcess::~ChunkedBodyProcess(void) {}

/*
StateType ChunkedBodyProcess::handle(Event *event)
{
	const std::string	bodyChunked = event->getReqRaw1();
	size_t				index;
	int					bodySize;
	std::string			body;

	//std::cout << "ChunkedBodyProcess" << std::endl;
	//std::cout << bodyChunked << std::endl;

	bodySize = -1;
	while (bodySize == -1)
	{
		if (event->getChunckSize() == -1)
		{
			index = bodyChunked.find("\r\n");
			if (index != bodyChunked.npos)
				bodySize = _hexToDec(bodyChunked.substr(0, index));
		}
		if (bodySize > 0)
		{
			body = bodyChunked.substr(index + 2, bodySize);
			if (bodySize == bodyChunked.size())
			{
				bodySize = -1;
				event->setReqBody(body);
			}
		}
		else if (bodySize == 0)
			return (REQUEST_END);
	}
	return (CHUNKED_BODY_PROCESS);


	//std::cout << body << std::endl;
	//std::cout << "bodySize: " << bodySize << std::endl;
	//std::cout << "bodySize: " << body.size() << std::endl;
}
*/

/*
StateType ChunkedBodyProcess::handle(Event *event)
{
	const std::string	bodyChunked = event->getReqRaw1();
	size_t				index;
	int					bodySize;
	std::string			body;

	bodySize = event->getChunckSize();

	if (bodySize == -1)
	{
		index = bodyChunked.find("\r\n");
		if (index != bodyChunked.npos)
				bodySize = _hexToDec(bodyChunked.substr(0, index));
	}
	if (bodySize > 0)
	{
		body = bodyChunked.substr(index + 2, bodySize);
		if (bodySize == body.size())
		{
			event->setReqBody(body);
			event->setReqRaw1(bodyChunked.substr(index + 2 + body.size() + 2)); // \r\n \r\n inicio final +4
		}
	}


	//return (CHUNKED_BODY_PROCESS);

	return (REQUEST_END);


	//std::cout << body << std::endl;
	//std::cout << "bodySize: " << bodySize << std::endl;
	//std::cout << "bodySize: " << body.size() << std::endl;
}
*/

StateType ChunkedBodyProcess::handle(Event *event)
{
	std::string	bodyChunked = event->getReqRaw1();
	size_t				index;
	int					bodySize;
	std::string			body;
	int					totalSize;

	while (true)
	{
		index = bodyChunked.find("\r\n");
		if (index == bodyChunked.npos)
			return (CHUNKED_BODY_PROCESS);
		bodySize = _hexToDec(bodyChunked.substr(0, index));

		if (bodySize == 0)
			return (REQUEST_END);
		index += 2;
		totalSize = index + bodySize + 2;
		if (totalSize > bodyChunked.size())
			return (CHUNKED_BODY_PROCESS);
		
		//std::cout << "---Body---" << std::endl;
		//std::cout << bodyChunked.substr(index, bodySize) << std::endl;
		
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
