/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:34:46 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/18 11:07:27 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <queue>

#include "IEventHandler.hpp"
#include "ReadHandler.hpp"
#include "WriteHandler.hpp"

class EventLoop
{
	private:
		std::map<EventType, IEventHandler*> _handlers;
		std::queue<int> _events;

	public:
		EventLoop(void);
		EventLoop(const EventLoop &src);
		~EventLoop(void);
		EventLoop &operator=(const EventLoop &src);

		void	registerEvent(IEventHandler *event);
		void	unregisterEvent(IEventHandler *event);
		void	handleEvents(void);

		void	addNewEvent(int event);
};
