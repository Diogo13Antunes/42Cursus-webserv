/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:34:46 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/22 11:40:25 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <queue>

#include "IEventHandler.hpp"
#include "ReadHandler.hpp"
#include "WriteHandler.hpp"
#include "Connections.hpp"
#include "IModule.hpp"
#include "Messenger.hpp"

class EventLoop: public IModule
{
	private:
		std::map<EventType, IEventHandler*> _handlers;
		std::queue<int>						_events;
		Messenger							*_messenger;
		
		void	_sendMessage(t_msg msg);

	public:
		EventLoop(void);
		EventLoop(Messenger *messenger);
		EventLoop(const EventLoop &src);
		~EventLoop(void);
		EventLoop &operator=(const EventLoop &src);

		void		registerEvent(IEventHandler *event);
		void		unregisterEvent(IEventHandler *event);
		void		handleEvents(void);

		void		addNewEvent(int event);

		ModuleID	getId(void);
		void		handleMessage(t_msg msg);
};
