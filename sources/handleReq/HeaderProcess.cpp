/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/02 14:24:14 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "HeaderProcess.hpp"
#include "RequestParser.hpp"


HeaderProcess::HeaderProcess(void) {}

HeaderProcess::~HeaderProcess(void) {}

StateType HeaderProcess::handle(Event *event)
{
	const std::string	req = event->getReqRaw1();
	size_t				headerEndIdx;
	RequestParser		parser;
	std::string			header;

	headerEndIdx = req.find("\r\n\r\n");
	if (headerEndIdx == req.npos)
		return (HEADER_PROCESS);

	header = req.substr(0, headerEndIdx + 4); // para remover provavelmente

	event->setReqRaw1(req.substr(headerEndIdx + 4));

	event->parseHeader(header); // para remover provavelmente

	// first verify if a error occors in parser

	if (_isChunkedTransfer(event))
		return (CHUNKED_BODY_PROCESS);
	if (event->getReqContentLength())
		return (BODY_PROCESS);
	return (REQUEST_END);
}

bool HeaderProcess::_isChunkedTransfer(Event *event)
{
	std::string transferEconding;

	transferEconding = event->getReqTransferEncoding();

	if (!transferEconding.compare("chunked"))
		return (true);
	else
		return (false);
}
