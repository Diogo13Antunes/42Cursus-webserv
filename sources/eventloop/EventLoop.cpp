/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/28 10:57:46 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EventLoop.hpp"

#include "CGIExecuter.hpp"

EventLoop::EventLoop(void): AMessengerClient(NULL) {}

EventLoop::EventLoop(const EventLoop &src) {}

EventLoop::~EventLoop(void) {}

void EventLoop::registerEventHandler(IEventHandler *eventHandler)
{
	EventType type;
	
	type = eventHandler->getHandleType();
	_handlers.insert(std::make_pair(type, eventHandler));
}

void EventLoop::unregisterEventHandler(IEventHandler *eventHandler)
{
	_handlers.erase(eventHandler->getHandleType());
}

void EventLoop::handleEvents(void)
{
	Event	*event;
	
	while (!_eventQueue.empty())
	{	
		event = _eventQueue.front();
		_handleEvent(event);
		_eventQueue.pop();
		if (event && event->getActualState() == TYPE_TRANSITION)
			_eventQueue.push(event);
		
		if (event->isFinished())
			_finalizeEvent(event);
		else if (event->isClientDisconnect())
			_handleClientDisconnect(event);
	}
	_checkIfCgiScriptsFinished();
	//_closeTimeoutEvents();
}

ClientID EventLoop::getId(void)
{
	return (EVENTLOOP_ID);
}

void EventLoop::receiveMessage(Message *msg)
{
	MessageType	type;
	int			fd;

	type = msg->getType();
	fd = msg->getFd();

	//std::cout << "Receive message: FD: " << fd  << " " << type << std::endl;

	if (type == EVENT_READ_TRIGGERED)
		_registerReadEvent(fd);
	else if (type == EVENT_WRITE_TRIGGERED)
		_registerWriteEvent(fd);
}

void EventLoop::_registerReadEvent(int fd)
{
	Event*	event;

	event = _getEventFromMap(_eventMap, fd);
	if (!event)
	{
		event = new Event(fd, READ_EVENT);
		_addEventToMap(event);
		sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_PAUSE_TIMER));
	}
	if (event->getActualState() == READ_EVENT && event->getFd() == fd)
		_addEventToQueue(event);
	else if (event->getActualState() == READ_CGI && event->getCgiReadFd() == fd)
		_addEventToQueue(event);
	else
		; // É porque ouve um pedido de fechar a ligacao fechar a ligação
}

void EventLoop::_registerWriteEvent(int fd)
{
	Event*		event;
	EventType	type;

	event = _getEventFromMap(_eventMap, fd);
	if (!event)
		return ;
	type = event->getActualState();
	if ((type == WRITE_EVENT && fd == event->getFd())
		|| (type == WRITE_CGI && fd == event->getCgiWriteFd()))
		_addEventToQueue(event);

}

void EventLoop::_handleEvent(Event *ev)
{
	std::map<EventType, IEventHandler*>::iterator	it;
	EventType										type;


	//getActualType()
	type = ev->getActualState();
	it = _handlers.find(type);
	if (it != _handlers.end())
		it->second->handleEvent(ev);
	if (type == TYPE_TRANSITION)
		_sendMessages(ev);
}


Event* EventLoop::_getEventFromMap(std::map<int, Event*> &map, int fd)
{
	std::map<int, Event*>::iterator	it;

	it = _eventMap.find(fd);
	if (it != _eventMap.end())
		return (it->second);
	return (NULL);
}

void EventLoop::_addEventToMap(Event *event)
{
	int	fd;

	fd = event->getFd();
	_eventMap.insert(std::make_pair(fd, event));
}

void EventLoop::_addEventToQueue(Event *event)
{
	_eventQueue.push(event);
}

void EventLoop::_deleteEvent(int fd)
{
	Event*	event;

	event = _getEventFromMap(_cgiEventMap, fd);
	if (event)
		_cgiEventMap.erase(fd);
	event = _getEventFromMap(_eventMap, fd);
	if (event)
	{
		_eventMap.erase(fd);
		delete event;	
	}
}

void EventLoop::_removeEventFromMap(std::map<int, Event*> &map, int fd)
{
	Event*	event;

	event = _getEventFromMap(map, fd);
	if (event)
		_eventMap.erase(fd);	
}

void EventLoop::_handleEventStates(Event *event)
{
	int fd;

	fd = event->getFd();

	if (event->getState() == READ_EVENT_COMPLETE)
	{
		event->setState(WRITE_EVENT);
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_WRITE));
	}
	else if (event->getState() == WRITE_EVENT_COMPLETE)
	{
		if (event->isConnectionClose())
		{
			sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
			sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));		
		}
		else
		{
			sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_READ));
			sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_RESTART_TIMER));
		}
		_deleteEvent(event->getFd());
	}
	else if(event->getState() == CGI_EVENT)
	{
		if (event->getCgiFd() == -1)
		{
			event->setCgiEx(new CGIExecuter());
			std::cout << "FD CGI: " << event->getCgiFd() << std::endl;
			_eventMap.insert(std::make_pair(event->getCgiFd(), event));
			_eventQueue.push(event);
			sendMessage(new Message(EVENTDEMUX_ID, event->getCgiFd(), EVENT_ADD_NEW));
		}
	}
	else if(event->getState() == CGI_EVENT_COMPLETE)
	{
		std::cout << "CGI completo" << std::endl;
		event->setState(WRITE_EVENT);
		_removeEventFromMap(_eventMap, event->getCgiFd());
		sendMessage(new Message(EVENTDEMUX_ID, event->getCgiFd(), EVENT_REMOVE));
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_WRITE));
	}
	else if (event->getState() == CLOSED_EVENT)
	{
		if (event->getCgiFd() > 0)
		{
			_removeEventFromMap(_eventMap, event->getCgiFd());
			sendMessage(new Message(EVENTDEMUX_ID, event->getCgiFd(), EVENT_REMOVE));
		}
		_deleteEvent(event->getFd());
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
		sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
	}
}

// Para não dar erro fazer depois de a queue estar vazia
void EventLoop::_closeTimeoutEvents(void)
{
	std::map<int, Event*>::iterator	it;
	Event							*event;
	int								fd;
	int								fdCgi;

	if (_eventMap.empty())
		return ;
	for (it = _eventMap.begin(); it != _eventMap.end(); it++)
	{
		event = it->second;
		fd = event->getFd();
		fdCgi = event->getCgiFd();
		if (fdCgi == it->first)
			continue ;
		if (event->isEventTimeout())
		{
			if (fdCgi)
			{
				_eventMap.erase(fdCgi);
				sendMessage(new Message(EVENTDEMUX_ID, fdCgi, EVENT_REMOVE));
			}
			_deleteEvent(fd);
			sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
			sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
		}
	}
}

void EventLoop::_checkIfCgiScriptsFinished(void)
{
	std::map<int, Event*>::iterator	itMap;
	Event							*event;
	int								fd;

	if (_cgiEventMap.empty())
		return ;
	itMap = _cgiEventMap.begin();
	while (itMap != _cgiEventMap.end())
	{
		event = itMap->second;
		if (event && event->getCgiExitStatus() == NO_EXIT_STATUS)
			event->isCgiScriptEnd();
		else if (event)
		{
			event->setActualState(TYPE_TRANSITION);
			_eventQueue.push(event);
			_cgiEventMap.erase(itMap);
			break;
		}
		itMap++;
	}
}

// NEW FUNCTIONS

void EventLoop::_sendMessages(Event *event)
{
	EventType	type;
	int			fd;
	
	type = event->getActualState(); // getActualType() mudar nome
	fd = event->getFd();

	if (type == WRITE_EVENT)
	{
		// Não pode ser assim tem de ter função de verificação se os cgi terminaram mas para já resolve sem erro

		//std::cout << "Vai para o evento de escrita" << std::endl;

		if (event->getCgiReadFd() > 0)
		{
			_removeEventFromMap(_eventMap, event->getCgiReadFd());
			sendMessage(new Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_REMOVE));
		}
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_WRITE));
	}
	else if (type == READ_EVENT)
	{
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_READ));
		sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_RESTART_TIMER));
	}
	else if (type == WRITE_CGI)
	{
		//std::cout << "Execute CGI WRITE_CGI" << std::endl;

		//Adicionar à lista de cgi verificar se o cgi falha
		//_cgiEventList.push_back(fd);

		_cgiEventMap.insert(std::make_pair(event->getFd(), event));

		//std::cout << "insere no mapa o CGI" << std::endl;

		event->cgiExecute();
		//std::cout << "CGI Write FD: " << event->getCgiWriteFd() << std::endl;
		
		_eventMap.insert(std::make_pair(event->getCgiWriteFd(), event));
		sendMessage(new Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_ADD_NEW));
		sendMessage(new Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_CHANGE_TO_WRITE));

		
		// tem de adicionar o fd de escrita ao mapa
		// tem de enviar menssagens para o EVENTDEMUX_ID para adicionar o evento 
	}
	else if (type == READ_CGI)
	{
		_removeEventFromMap(_eventMap, event->getCgiWriteFd());
		sendMessage(new Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_REMOVE));
		_eventMap.insert(std::make_pair(event->getCgiReadFd(), event));
		sendMessage(new Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_ADD_NEW));
		//_cgiReadFdsVec.a
	}
}

void EventLoop::_finalizeEvent(Event *event)
{
	int	fd;
	
	fd = event->getFd();
	if (event->isConnectionClose())
	{
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
		sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
	}
	_deleteEvent(fd);
}

void EventLoop::_handleClientDisconnect(Event *event)
{
	int	fd;

	fd = event->getFd();
	sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
	sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
	_deleteEvent(fd);
}
