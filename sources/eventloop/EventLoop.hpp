/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:34:46 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/25 19:08:41 by dsilveri         ###   ########.fr       */
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
#include "ReadCgiHandler.hpp"
#include "WriteCgiHandler.hpp"
#include "TypeTransitionHandler.hpp"
#include "AMessengerClient.hpp"
#include "Event.hpp"

class EventLoop: public AMessengerClient
{
	private:
		std::map<EventType, IEventHandler*> _handlers;
		std::map<int, Event*>				_eventMap;
		std::queue<Event*>					_eventQueue;

		void	_changeEvent(Event *ev, short status);
		void	_handleEvent(Event *ev);
		Event*	_getEventFromMap(int fd);
		void	_addEventToMap(Event *event);
		void	_addEventToQueue(Event *event);
		void	_registerReadEvent(int fd);
		void	_registerWriteEvent(int fd);
		void	_deleteEvent(int fd);
		void	_removeEventFromMap(int fd);
		void	_handleEventStates(Event *event);
		void	_closeTimeoutEvents(void);
		void 	_checkIfCgiScriptsFinished(void);

		void	_sendMessages(Event *event);

		void _finalizeEvent(Event *event);
		void _handleClientDisconnect(Event *event);


	public:
		EventLoop(void);
		EventLoop(const EventLoop &src);
		~EventLoop(void);
		EventLoop &operator=(const EventLoop &src);

		void		registerEventHandler(IEventHandler *eventHandler);
		void		unregisterEventHandler(IEventHandler *eventHandler);
		void		handleEvents(void);


		ClientID	getId(void);
		void		receiveMessage(Message *msg);
};
