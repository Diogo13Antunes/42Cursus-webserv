/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/21 10:01:33 by dsilveri         ###   ########.fr       */
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
	header = req.substr(0, headerEndIdx + 4);

	event->setReqRaw1(req.substr(headerEndIdx + 4));

	// nova funcao
	event->parseHeader(header);

	// não deve ser feito aqui
	//cgi deixou de funcionar devido ao novo parser do header resolver depois
	if (!event->getReqLinePath().compare("/cgi"))
		event->setCgiFlag(true);
	// não deve ser feito aqui
	if (!event->getBodySize())
		return (REQUEST_END);
	return (BODY_PROCESS);
}