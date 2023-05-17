/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandlerFactory.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:03:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/17 19:05:49 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventHandlerFactory.hpp"

EventHandlerFactory::EventHandlerFactory(void)
{
	//Default EventHandlerFactory Constructor
}

EventHandlerFactory::EventHandlerFactory(const EventHandlerFactory &src)
{
	//EventHandlerFactory Copy Constructor
}

EventHandlerFactory::~EventHandlerFactory(void)
{
	//Default EventHandlerFactory Destructor
}
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