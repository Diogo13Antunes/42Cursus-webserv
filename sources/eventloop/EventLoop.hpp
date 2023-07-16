/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:34:46 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/16 09:29:49 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <queue>
#include <set>

#include "IEventHandler.hpp"
#include "ReadHandler.hpp"
#include "WriteHandler.hpp"
#include "CGIHandler.hpp"
#include "AMessengerClient.hpp"
#include "Event.hpp"

class EventLoop: public AMessengerClient
{
	private:
		std::map<EventType, IEventHandler*> _handlers;
		std::map<int, Event*>				_eventMap;
		std::queue<Event*>					_eventQueue;

		//void	_handleMessage(EventMessage *msg);
		//void	_addNewEvent(Event *ev);


		void	_changeEvent(Event *ev, short status);
		//Event*	_handleNextEvent(void);
		void	_handleEvent(Event *ev);
		Event*	_getEventFromMap(int fd);
		void	_addEventToMap(Event *event);
		void	_addEventToQueue(Event *event);
		void	_registerReadEvent(int fd);
		void	_registerWriteEvent(int fd);
		void	_deleteEvent(int fd);
		void	_handleEventStates(Event *event);

	public:
		EventLoop(void);
		EventLoop(const EventLoop &src);
		~EventLoop(void);
		EventLoop &operator=(const EventLoop &src);

		void		registerEventHandler(IEventHandler *event);
		void		unregisterEventHandler(IEventHandler *event);
		void		handleEvents(void);

		ClientID	getId(void);
		void		receiveMessage(Message *msg);
};
