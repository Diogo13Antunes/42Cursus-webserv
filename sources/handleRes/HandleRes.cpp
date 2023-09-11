/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:52:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 20:08:49 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRes.hpp"
#include <iostream>
#include <sys/socket.h>

#include "InitialState.hpp"
#include "ErrorHandlingState.hpp"
#include "DirectoryListingState.hpp"
#include "StaticFileHandlingState.hpp"
#include "RedirectionHandlingState.hpp"
#include "ResponseState.hpp"
#include "CgiResponseHandlingState.hpp"

HandleRes::HandleRes(void):
	_event(NULL),
	_serverConf(NULL)
{
	_stateMap.insert(std::make_pair(INITIAL_STATE, new InitialState()));
	_stateMap.insert(std::make_pair(ERROR_HANDLING, new ErrorHandlingState()));
	_stateMap.insert(std::make_pair(REDIRECTION_HANDLING, new RedirectionHandlingState()));
	_stateMap.insert(std::make_pair(DIRECTORY_LISTING, new DirectoryListingState()));
	_stateMap.insert(std::make_pair(STATIC_FILE_HANDLING, new StaticFileHandlingState()));
	_stateMap.insert(std::make_pair(CGI_RES_HANDLING, new CgiResponseHandlingState()));
	_stateMap.insert(std::make_pair(RESPONSE, new ResponseState()));
}

HandleRes::~HandleRes(void)
{
	std::map<StateResType, IStateRes*>::iterator	it;

	it = _stateMap.begin();
	while (it !=  _stateMap.end())
	{
		if (it->second)
			delete it->second;
		it++;
	}
}

void HandleRes::setEvent(Event *event)
{
	_event = event;
}

void HandleRes::handle(void)
{
	StateResType	state;
	bool			loop;

	_serverConf = _event->getServerConfing();
	if (!_serverConf)
		_event->setStatusCode(INTERNAL_SERVER_ERROR);
	loop = true;
	while (loop && _event->getResState1() != RESPONSE_END)
	{
		if (_event->getResState1() == RESPONSE)
			loop = false;
		state = _handleState(_event->getResState1());
		_event->setResState1(state);
	}
}

StateResType HandleRes::_handleState(StateResType state)
{
	std::map<StateResType, IStateRes*>::iterator	it;

	if (state != RESPONSE_END)
	{
		it = _stateMap.find(state);
		if (it != _stateMap.end())
			state = it->second->handle(_event, *_serverConf);
	}
	return (state);
}

bool HandleRes::isResProcessingComplete(void)
{
	if (_event->getResState1() == RESPONSE_END)
		return (true);
	return (false);
}
