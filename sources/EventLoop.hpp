/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:34:46 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/17 17:56:03 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>

#include "IEventHandler.hpp"
#include "ReadHandler.hpp"
#include "WriteHandler.hpp"

class EventLoop
{
	std::map<EventType, IEventHandler*> _handlers;

	public:
		EventLoop(void);
		EventLoop(const EventLoop &src);
		~EventLoop(void);
		EventLoop &operator=(const EventLoop &src);

		void	registerEvent(IEventHandler *event);
		void	unregisterEvent(IEventHandler *event);
		void	handleEvents(void);
};
