/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleReq.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:15:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 11:12:49 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleReq.hpp"
#include "HeaderProcess.hpp"
#include "BodyProcess.hpp"
#include "ChunkedBodyProcess.hpp"

HandleReq::HandleReq(void): _event(NULL)
{
	_stateMap.insert(std::make_pair(HEADER_PROCESS, new HeaderProcess()));
	_stateMap.insert(std::make_pair(BODY_PROCESS, new BodyProcess()));
	_stateMap.insert(std::make_pair(CHUNKED_BODY_PROCESS, new ChunkedBodyProcess()));
}

HandleReq::~HandleReq(void)
{
	std::map<StateReqType, IState*>::iterator	it;

	it = _stateMap.begin();
	while (it != _stateMap.end())
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

bool HandleReq::_changeState(StateReqType newState)
{
	if (_event->getReqState() != newState)
	{
		_event->setReqState(newState);
		return (true);
	}
	return (false);
}

StateReqType HandleReq::_handleCurrentState(StateReqType state)
{
	std::map<StateReqType, IState*>::iterator	it;

	if (state != REQUEST_END)
	{
		it = _stateMap.find(state);
		if (it != _stateMap.end())
			state = it->second->handle(_event);
		else
			state = REQUEST_END;
	}
	return (state);
}

bool HandleReq::isProcessingComplete(void)
{
	if (_event->getReqState() == REQUEST_END)
		return (true);
	return (false);
}
