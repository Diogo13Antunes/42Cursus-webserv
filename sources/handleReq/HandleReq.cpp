/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleReq.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:15:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/02 14:23:22 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleReq.hpp"

HandleReq::HandleReq(void): _event(NULL)
{
	_stateMap.insert(std::make_pair(HEADER_PROCESS, new HeaderProcess()));
	_stateMap.insert(std::make_pair(BODY_PROCESS, new BodyProcess()));
	_stateMap.insert(std::make_pair(CHUNKED_BODY_PROCESS, new ChunkedBodyProcess()));
}

HandleReq::~HandleReq(void)
{
	std::map<StateType, IState*>::iterator	it;

	it = _stateMap.begin();
	while (it !=  _stateMap.end())
	{
		if (it->second)
			delete it->second;
		it++;
	}
}

void HandleReq::setEvent(Event *event)
{
	_event = event;
}

void HandleReq::handle(void)
{
	while (_changeState(_handleCurrentState(_event->getReqState())));
}

bool HandleReq::_changeState(StateType newState)
{
	if (_event->getReqState() != newState)
	{
		_event->setReqState(newState);
		return (true);
	}
	return (false);
}

StateType HandleReq::_handleCurrentState(StateType state)
{
	std::map<StateType, IState*>::iterator	it;

	if (state != REQUEST_END)
	{
		it = _stateMap.find(state);
		if (it != _stateMap.end())
			state = it->second->handle(_event);
	}
	return (state);
}

bool HandleReq::isProcessingComplete(void)
{
	if (_event->getReqState() == REQUEST_END)
		return (true);
	return (false);
}
