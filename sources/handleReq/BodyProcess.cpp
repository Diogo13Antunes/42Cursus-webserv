/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/01 10:23:15 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyProcess.hpp"

BodyProcess::BodyProcess(void) {}

BodyProcess::~BodyProcess(void) {}

StateReqType BodyProcess::handle(Event *event)
{
	event->updateReqBody(event->getReqRawData());
	event->clearReqRawData();
	if (event->getReqBodySize() >= event->getReqContentLength())
		return (REQUEST_END);
	return (BODY_PROCESS);
}
