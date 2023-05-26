/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEventHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:48:24 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/26 11:29:12 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Event.hpp"

typedef enum 
{
    READ_EVENT = 0,
    WRITE_EVENT
}	EventType;

class IEventHandler
{
	public:
		virtual ~IEventHandler(void) {};

		virtual void handleEvent(Event *event) = 0;
		virtual EventType getHandleType(void) = 0;
};
