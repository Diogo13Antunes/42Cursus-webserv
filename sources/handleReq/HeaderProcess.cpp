/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/05 15:28:46 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "HeaderProcess.hpp"
#include "RequestParser.hpp"


HeaderProcess::HeaderProcess(void) {}

HeaderProcess::~HeaderProcess(void) {}

StateReqType HeaderProcess::handle(Event *event)
{
	std::string header;

	if (!event->isReqHeaderComplete())
		return (HEADER_PROCESS);
	header = event->getReqHeader();
	event->parseReqHeader(header);

	if (event->getStatusCode())
		return (REQUEST_END);

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
