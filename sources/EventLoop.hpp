/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:34:46 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/31 16:42:41 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <queue>
#include <set>

#include "IEventHandler.hpp"
#include "ReadHandler.hpp"
#include "WriteHandler.hpp"
#include "AMessengerClient.hpp"
#include "Event.hpp"
#include "EventMessage.hpp"

class EventLoop: public AMessengerClient
{
	private:
		std::map<EventType, IEventHandler*> _handlers;
		std::map<int, Event*>				_eventsMap; //passar para _eventMap

		//std::queue<int>						_events; // para remover

		std::queue<Event*>					_readQueue;
		std::queue<Event*>					_writeQueue;

		std::queue<Event*>					_eventQueue;
		

		//Messenger							*_messenger;
		
		//void	_sendMessage(t_msg msg);

	public:
		EventLoop(void);
		EventLoop(Messenger *messenger);
		EventLoop(const EventLoop &src);
		~EventLoop(void);
		EventLoop &operator=(const EventLoop &src);

		void		registerEvent(IEventHandler *event);
		void		unregisterEvent(IEventHandler *event);
		void		handleEvents(void);

		ClientID	getId(void);
		void		receiveMessage(Message *msg);
};
