/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:34:46 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/20 11:27:58 by dsilveri         ###   ########.fr       */
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
		void	_addEventToQueue(int fd);
		Event* 	_getEventFromMap(std::map<int, Event*> &map, int fd);
		void	_deleteEvent(int fd);
		void	_closeTimeoutEvents(void);
		void 	_checkIfCgiScriptsFinished(void);
		int		_getNextEventFromQueue(void);
		void	_cleanHandlers(void);
		void	_cleanEvents(void);
		void	_changeEventStatus(Event *event);
		void	_changeToWriteCgi(Event *event);
		void	_changeToReadCgi(Event *event);
		void	_changeToWriteSocket(Event *event);
		void	_closeEvent(Event *event);
		void	_disconnectEvent(Event *event);
		void	_insertEventToMap(std::map<int, Event*> &map, int fd, Event *event);
		void	_removeCgiFd(Event *event, int cgiFd);
		void	_removeAllCgiFds(Event *event);

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
