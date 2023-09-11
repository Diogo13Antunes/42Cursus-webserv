/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 08:41:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyProcess.hpp"

BodyProcess::BodyProcess(void) {}

BodyProcess::~BodyProcess(void) {}

StateReqType BodyProcess::handle(Event *event, ConfigsData *configsData)
{
	event->updateReqBody(event->getReqRawData());
	event->clearReqRawData();
	if (event->getReqBodySize() >= event->getReqContentLength())
		return (REQUEST_END);
	return (BODY_PROCESS);
}
