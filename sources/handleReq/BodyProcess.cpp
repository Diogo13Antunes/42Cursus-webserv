/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 11:08:19 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyProcess.hpp"
#include "RequestParser.hpp"

BodyProcess::BodyProcess(void) {}

BodyProcess::~BodyProcess(void) {}

StateReqType BodyProcess::handle(Event *event)
{
	event->updateReqBody(event->getReqRaw1());
	event->setReqRaw1(""); // mudar nome

	if (event->getReqBodySize() >= event->getReqContentLength())
		return (REQUEST_END);
	return (BODY_PROCESS);
}
