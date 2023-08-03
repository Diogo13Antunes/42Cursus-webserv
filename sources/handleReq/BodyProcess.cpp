/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/03 16:30:24 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyProcess.hpp"
#include "RequestParser.hpp"

BodyProcess::BodyProcess(void) {}

BodyProcess::~BodyProcess(void) {}

/*
StateType BodyProcess::handle(Event *event)
{
	const std::string	req = event->getReqRaw1();
	std::string			body;

	if (event->getReqContentLength() != req.size())
		return (BODY_PROCESS);

	body = req;
	event->setReqBody(body);

	//std::cout << "---BODY---" << std::endl;
	//std::cout << body << std::endl;

	return (REQUEST_END);
}
*/

StateType BodyProcess::handle(Event *event)
{
	event->updateReqBody(event->getReqRaw1());
	event->setReqRaw1("");

	if (event->getReqBodySize() >= event->getReqContentLength())
	{
		//std::cout << event->getReqBody() << std::endl;
		return (REQUEST_END);
	}
	return (BODY_PROCESS);
}
