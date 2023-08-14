/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:52:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/14 16:13:02 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <cstdlib> // para remover apenas de teste


#include <iostream>
#include <sys/socket.h>

#include "HandleRes.hpp"

HandleRes::HandleRes(void):
	_event(NULL),
	_state(CREATE_HEADER)
{
	_stateMap.insert(std::make_pair(CREATE_HEADER, new CreateHeaderState()));
	_stateMap.insert(std::make_pair(CGI_RES_PROCESS, new CgiResponseProcess()));
	_stateMap.insert(std::make_pair(GET_BODY, new GetBodyState()));
	_stateMap.insert(std::make_pair(RESPONSE, new ResponseState()));
}

HandleRes::HandleRes(ConfigsData &configsData):
	_event(NULL),
	_configsData(configsData),
	_state(CREATE_HEADER) //maybe not nedded
{
	_stateMap.insert(std::make_pair(CREATE_HEADER, new CreateHeaderState()));
	_stateMap.insert(std::make_pair(CGI_RES_PROCESS, new CgiResponseProcess()));
	_stateMap.insert(std::make_pair(GET_BODY, new GetBodyState()));
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

	// For send data from cgi. Will be changed
	loop = true;
	if (!_event->getCgiScriptResult().empty() && _event->getResState1() != RESPONSE)
		_event->setResState1(CGI_RES_PROCESS);
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
			state = it->second->handle(_event, _configsData);
	}
	return (state);
}

bool HandleRes::isResProcessingComplete(void)
{
	if (_event->getResState1() == RESPONSE_END)
		return (true);
	return (false);
}
