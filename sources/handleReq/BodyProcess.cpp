/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/23 14:59:24 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyProcess.hpp"
#include "configs.hpp"

BodyProcess::BodyProcess(void) {}

BodyProcess::~BodyProcess(void) {}

StateReqType BodyProcess::handle(Event *event, ConfigsData *configsData)
{
	(void)configsData;
	event->updateReqBody(event->getReqRawData());
	if (event->getReqRawData().empty() && event->getReqContentLength())
	{
		event->setStatusCode(BAD_REQUEST_CODE);
		return (REQUEST_END);
	}
	event->clearReqRawData();
	if (event->getReqBodySize() == event->getReqContentLength())
		return (REQUEST_END);
	if (event->getReqBodySize() > event->getReqContentLength())
	{
		event->setStatusCode(CONTENT_TOO_LARGE_CODE);
		return (REQUEST_END);
	}
	return (BODY_PROCESS);
}
