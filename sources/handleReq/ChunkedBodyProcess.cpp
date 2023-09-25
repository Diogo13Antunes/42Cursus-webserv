/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkedBodyProcess.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:19:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/25 10:06:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChunkedBodyProcess.hpp"
#include "configs.hpp"
#include <iostream>

ChunkedBodyProcess::ChunkedBodyProcess(void) {}

ChunkedBodyProcess::~ChunkedBodyProcess(void) {}

StateReqType ChunkedBodyProcess::handle(Event *event, ConfigsData *configsData)
{
	std::string		bodyChunked = event->getReqRaw1();
	size_t			index;
	size_t			bodySize;
	std::string		body;
	size_t			totalSize;
	ServerConfig*	serverConf;
	std::string		route;

	(void)configsData;
	serverConf = event->getServerConfing();
	route = event->getRoute();
	while (true)
	{
		index = bodyChunked.find("0\r\n\r\n");
		if (index == 0)
			return (REQUEST_END);
		index = bodyChunked.find("\r\n");
		if (index == bodyChunked.npos)
			break ;
		bodySize = _hexToDec(bodyChunked.substr(0, index));
		if (bodySize == 0)
			break ;
		index += 2;
		totalSize = index + bodySize + 2;
		if (totalSize >= bodyChunked.size())
			break ;
		event->updateReqBody(bodyChunked.substr(index, bodySize));
		event->setReqRaw1(bodyChunked.substr(totalSize));
		bodyChunked = bodyChunked.substr(totalSize);
		if (event->getReqBodySize() > serverConf->getLocationBodySize(route))
		{
			event->setStatusCode(CONTENT_TOO_LARGE_CODE);
			return (REQUEST_END);
		}
	}
	return (CHUNKED_BODY_PROCESS);
}


size_t ChunkedBodyProcess::_hexToDec(std::string hex)
{
	std::stringstream	ss;
	size_t				res;

	ss << std::hex << hex;
	ss >> res;
	return (res);
}
