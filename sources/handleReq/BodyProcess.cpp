/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/24 16:20:46 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyProcess.hpp"
#include "RequestParser.hpp"

BodyProcess::BodyProcess(void)
{
	//Default BodyProcess Constructor
}

BodyProcess::BodyProcess(const BodyProcess &src)
{
	//BodyProcess Copy Constructor
}

BodyProcess::~BodyProcess(void)
{
	//Default BodyProcess Destructor
}

/*
BodyProcess &BodyProcess::operator=(const BodyProcess &src)
{
	//BodyProcess Copy Assignment Operator
}
*/

StateType BodyProcess::handle(Event *event)
{
	const std::string	req = event->getReqRaw1();
	RequestParser		parser;
	std::string			body;
	
	std::cout << "BodyProcess" << std::endl;

	if (event->getBodySize() != req.size())
		return (BODY_PROCESS);

	body = req;
	parser.bodyParse(body);
	event->setResquestBody(parser.getRequestBody());
	
	return (REQUEST_END);
}
