/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/21 10:08:40 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyProcess.hpp"
#include "RequestParser.hpp"

BodyProcess::BodyProcess(void) {}

BodyProcess::~BodyProcess(void) {}

StateType BodyProcess::handle(Event *event)
{
	const std::string	req = event->getReqRaw1();
	RequestParser		parser;
	std::string			body;
	
	if (event->getBodySize() != req.size())
		return (BODY_PROCESS);

	body = req;
	parser.bodyParse(body);//provavelmente tem de ser alterado
	event->setResquestBody(parser.getRequestBody());
	
	return (REQUEST_END);
}
