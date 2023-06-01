/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandlerFactory.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:03:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 11:13:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventHandlerFactory.hpp"

EventHandlerFactory::EventHandlerFactory(void) {}

EventHandlerFactory::EventHandlerFactory(const EventHandlerFactory &src) {}

EventHandlerFactory::~EventHandlerFactory(void) {}

/*
EventHandlerFactory &EventHandlerFactory::operator=(const EventHandlerFactory &src)
{
	//EventHandlerFactory Copy Assignment Operator
}
*/

IEventHandler* EventHandlerFactory::getEventHandler(EventType type)
{
	if (type == READ_EVENT)
		return (new ReadHandler());
	else if (type == WRITE_EVENT)
		return (new WriteHandler());
	else 
		return (NULL);
}
