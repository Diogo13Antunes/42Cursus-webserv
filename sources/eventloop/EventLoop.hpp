/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:34:46 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/15 15:24:51 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <queue>
#include <list>

#include "IEventHandler.hpp"
#include "ReadSocketHandler.hpp"
#include "WriteHandler.hpp"
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
		std::map<int, Event*>				_cgiEventMap;
		std::queue<int>						_eventQueue;

		void	_handleEvent(Event *ev);
		void	_registerReadEvent(int fd);
		void	_registerWriteEvent(int fd);
		void	_addEventToMap(Event *event);
		void	_addEventToMap(int fd, Event *event);
		void	_addEventToQueue(int fd);
		Event* 	_getEventFromMap(std::map<int, Event*> &map, int fd);
		void	_deleteEvent(int fd);
		void	_closeTimeoutEvents(void);
		void 	_checkIfCgiScriptsFinished(void);
		void	_finalizeEvent(Event *event);
		void	_handleClientDisconnect(Event *event);
		int		_getNextEventFromQueue(void);
		void	_sendMessages(Event *event);
		void	_cleanHandlers(void);
		void	_cleanEvents(void);
		
		// NEW
		void _changeEventStatus(Event *event);

		// DEBUG
		void _showEventMap(void);
		void _showCgiEventMap(void);

	public:
		EventLoop(void);
		~EventLoop(void);

		void		registerEventHandler(IEventHandler *eventHandler);
		void		unregisterEventHandler(IEventHandler *eventHandler);
		void		handleEvents(void);
		ClientID	getId(void);
		void		receiveMessage(Message msg);

};
