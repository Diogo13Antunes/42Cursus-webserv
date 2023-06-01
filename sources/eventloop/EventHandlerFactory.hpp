/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventHandlerFactory.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:03:49 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/17 19:53:54 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"
#include "ReadHandler.hpp"
#include "WriteHandler.hpp"

class EventHandlerFactory
{
	public:
		EventHandlerFactory &operator=(const EventHandlerFactory &src);
		EventHandlerFactory(const EventHandlerFactory &src);
		EventHandlerFactory(void);
		~EventHandlerFactory(void);

		IEventHandler *getEventHandler(EventType type);
};
