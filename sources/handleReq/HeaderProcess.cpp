/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/25 10:30:27 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "HeaderProcess.hpp"
#include "RequestParser.hpp"


HeaderProcess::HeaderProcess(void)
{
	//Default HeaderProcess Constructor
}

HeaderProcess::HeaderProcess(const HeaderProcess &src)
{
	//HeaderProcess Copy Constructor
}

HeaderProcess::~HeaderProcess(void)
{
	//Default HeaderProcess Destructor
}

/*
HeaderProcess &HeaderProcess::operator=(const HeaderProcess &src)
{
	//HeaderProcess Copy Assignment Operator
}
*/

/*
StateType HeaderProcess::handle(Event *event)
{

	std::cout << "HeaderProcess" << std::endl;

	std::cout << "HEADER: " << event->getHeaderRaw1() << std::endl;

	return (HEADER_PROCESS);
}
*/

StateType HeaderProcess::handle(Event *event)
{
	const std::string	req = event->getReqRaw1();
	size_t				headerEndIdx;
	RequestParser		parser;
	std::string			header;

	headerEndIdx = req.find("\r\n\r\n");
	if (headerEndIdx == std::string::npos)
		return (HEADER_PROCESS);
	//event->setHeaderRaw(req.substr(0, headerEndIdx + 4));

	header = req.substr(0, headerEndIdx + 4);
	event->setReqRaw1(req.substr(headerEndIdx + 4));
	parser.headerParse(header);
	event->setResquestHeader(parser.getRequestLine(), parser.getRequestHeader());
	if (!event->getBodySize())
		return (REQUEST_END);
	return (BODY_PROCESS);
}
