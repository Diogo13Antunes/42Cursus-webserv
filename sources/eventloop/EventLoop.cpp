/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventLoop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/01 09:50:31 by dsilveri         ###   ########.fr       */
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

/*
void EventLoop::handleEvents(void)
{
	Event	*event;
	
	while (!_eventQueue.empty())
	{	
		
		event = _eventQueue.front();
		_handleEvent(event);
		_eventQueue.pop();

		if (event && event->isClientDisconnect())
		{
 			_handleClientDisconnect(event);
			continue ;
		}
		if (event && event->isFinished())
		{
			_finalizeEvent(event);
			continue ;
		}
		if (event && event->getActualState() == TYPE_TRANSITION)
			_eventQueue.push(event);
	}
	_checkIfCgiScriptsFinished();
	//_closeTimeoutEvents();
}
*/


void EventLoop::handleEvents(void)
{
	Event	*event;
	int		fd;
	
	while (!_eventQueue1.empty())
	{	
		
		fd = _eventQueue1.front();
		_eventQueue1.pop();
		event = _getEventFromMap(_eventMap, fd);
		if (event)
			_handleEvent(event);
		if (event && event->isClientDisconnect())
		{
 			_handleClientDisconnect(event);
			continue ;
		}
		if (event && event->isFinished())
		{
			_finalizeEvent(event);
			continue ;
		}
		if (event && event->getActualState() == TYPE_TRANSITION)
			_eventQueue1.push(event->getFd());
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
	if (event && event->getActualState() == READ_EVENT && event->getFd() == fd)
		_addEventToQueue(event);
	else if (event && event->getActualState() == READ_CGI && event->getCgiReadFd() == fd)
		_addEventToQueue(event);
	else if (event)
		_handleClientDisconnect(event);
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

	if (ev)
	{
		type = ev->getActualState();
		it = _handlers.find(type);
		if (it != _handlers.end())
			it->second->handleEvent(ev);
		if (type == TYPE_TRANSITION)
			_sendMessages(ev);
	}
}

Event* EventLoop::_getEventFromMap(std::map<int, Event*> &map, int fd)
{
	std::map<int, Event*>::iterator	it;

	it = map.find(fd);
	if (it != map.end())
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
	//_eventQueue.push(event);
	_eventQueue1.push(event->getFd());
}

void EventLoop::_deleteEvent(int fd)
{
	Event*	event;
	Event**	eventPtr;
	int		cgiReadFd;
	int		cgiWriteFd;

	event = _getEventFromMap(_cgiEventMap, fd);
	if (event)
		_cgiEventMap.erase(fd);
	event = _getEventFromMap(_eventMap, fd);
	if (event)
	{
		cgiReadFd = event->getCgiReadFd();
		cgiWriteFd = event->getCgiWriteFd();
		if (_getEventFromMap(_eventMap, cgiReadFd))
			_eventMap.erase(cgiReadFd);
		if (_getEventFromMap(_eventMap, cgiWriteFd))
			_eventMap.erase(cgiWriteFd);
		_eventMap.erase(fd);
		delete event;
	}
}

/*
Event** EventLoop::_getDoublePointerToEvent(int fd)
{
	std::map<int, Event*>::iterator	it;

	it = _eventMap.find(fd);
	if (it != _eventMap.end())
		return (&(it->second));
	return (NULL);
}
*/

/*
void EventLoop::_removeEventFromMap(std::map<int, Event*> &map, int fd)
{
	Event*	event;

	event = _getEventFromMap(map, fd);
	if (event)
		_eventMap.erase(fd);	
}
*/

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

/*
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
	//std::cout << "CGImapsize: " << _cgiEventMap.size() << std::endl;
}
*/

/*
void EventLoop::_checkIfCgiScriptsFinished(void)
{
	std::map<int, Event*>::iterator	itMap;
	std::map<int, Event*>::iterator	itMapBackUp;
	Event							*event;
	int								fd;
	int								status;

	if (_cgiEventMap.empty())
		return ;
	itMap = _cgiEventMap.begin();
	while (itMap != _cgiEventMap.end())
	{
		fd = itMap->first;
		if (!_getEventFromMap(_eventMap, fd))
		{
			_cgiEventMap.erase(itMap);
			continue ;
		}
		event = itMap->second;
		status = event->getCgiExitStatus();
		if (status == NO_EXIT_STATUS)
			event->isCgiScriptEnd();
		else if (status != NO_EXIT_STATUS)
		{
			event->setActualState(TYPE_TRANSITION);
			_eventQueue.push(event);
			itMapBackUp = itMap;
			itMapBackUp++;
			_cgiEventMap.erase(itMap);
			itMap = itMapBackUp;
			continue ;
		}
		itMap++;
	}
	//std::cout << "CGImapsize: " << _cgiEventMap.size() << std::endl;
}
*/

void EventLoop::_checkIfCgiScriptsFinished(void)
{
	std::map<int, Event*>::iterator	itMap;
	std::map<int, Event*>::iterator	itMapBackUp;
	Event							*event;
	int								fd;
	int								status;

	if (_cgiEventMap.empty())
		return ;
	itMap = _cgiEventMap.begin();
	while (itMap != _cgiEventMap.end())
	{
		fd = itMap->first;
		if (!_getEventFromMap(_eventMap, fd))
		{
			_cgiEventMap.erase(itMap);
			continue ;
		}
		event = itMap->second;
		status = event->getCgiExitStatus();
		if (status == NO_EXIT_STATUS)
			event->isCgiScriptEnd();
		else if (status != NO_EXIT_STATUS)
		{
			event->setActualState(TYPE_TRANSITION);
			_eventQueue1.push(event->getFd());
			itMapBackUp = itMap;
			itMapBackUp++;
			_cgiEventMap.erase(itMap);
			itMap = itMapBackUp;
			continue ;
		}
		itMap++;
	}
	//std::cout << "CGImapsize: " << _cgiEventMap.size() << std::endl;
}

// NEW FUNCTIONS

void EventLoop::_sendMessages(Event *event)
{
	EventType	type;
	int			fd;
	
	type = event->getActualState(); // getActualType() mudar nome
	fd = event->getFd();

	/*if (type == WRITE_EVENT)
	{
		// Não pode ser assim tem de ter função de verificação se os cgi terminaram mas para já resolve sem erro

		//std::cout << "Vai para o evento de escrita" << std::endl;

		if (event->getCgiReadFd() > 0)
		{
			//_removeEventFromMap(_eventMap, event->getCgiReadFd());
			//sendMessage(new Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_REMOVE));
		}
		sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_CHANGE_TO_WRITE));

	}*/

	if (type == WRITE_EVENT)
	{

		/*if (event->getCgiReadFd() > 0 && event->getCgiWriteFd() > 0)
		{
			_removeEventFromMap(_eventMap, event->getCgiReadFd());
			_removeEventFromMap(_eventMap, event->getCgiWriteFd());
			sendMessage(new Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_REMOVE));
			sendMessage(new Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_REMOVE));
		}*/

		if (event->getCgiReadFd() > 0)
		{
			//_removeEventFromMap(_eventMap, event->getCgiReadFd());
			sendMessage(new Message(EVENTDEMUX_ID, event->getCgiReadFd(), EVENT_REMOVE));
		}
		if (event->getCgiWriteFd() > 0)
		{
			//_removeEventFromMap(_eventMap, event->getCgiWriteFd());
			sendMessage(new Message(EVENTDEMUX_ID, event->getCgiWriteFd(), EVENT_REMOVE));
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
		//_removeEventFromMap(_eventMap, event->getCgiWriteFd()); // ao remover colocar fd a -1
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
		// aqui chamar o _handleClientDisconnect
		_handleClientDisconnect(event);
		//sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
		//sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
	}
	else
		_deleteEvent(fd);
}

void EventLoop::_handleClientDisconnect(Event *event)
{
	int			fd;
	int			cgiReadFd;
	int			cgiWriteFd;
	EventType	type;
	
	fd = event->getFd();
	cgiReadFd = event->getCgiReadFd();
	cgiWriteFd = event->getCgiWriteFd();
	type = event->getActualState();
	sendMessage(new Message(EVENTDEMUX_ID, fd, EVENT_REMOVE));
	sendMessage(new Message(CONNECTIONS_ID, fd, CONNECTION_REMOVE));
	if (cgiReadFd > 0 && type == READ_CGI)
		sendMessage(new Message(EVENTDEMUX_ID, cgiReadFd, EVENT_REMOVE));
	if (cgiWriteFd > 0 && type == WRITE_CGI)
		sendMessage(new Message(EVENTDEMUX_ID, cgiWriteFd, EVENT_REMOVE));
	_deleteEvent(fd);
}
