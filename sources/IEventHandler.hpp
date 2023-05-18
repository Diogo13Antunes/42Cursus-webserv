/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEventHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:48:24 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/18 12:07:57 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

typedef enum 
{
    READ_EVENT,
    WRITE_EVENT
}	EventType;

class IEventHandler
{
	public:
		virtual ~IEventHandler(void) {};

		virtual void handleEvent(int event) = 0;
		virtual EventType getHandleType(void) = 0;
};
