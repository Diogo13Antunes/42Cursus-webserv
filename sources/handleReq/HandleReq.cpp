/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleReq.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:15:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/29 16:33:07 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleReq.hpp"

HandleReq::HandleReq(void): _event(NULL)
{
	_stateMap.insert(std::make_pair(HEADER_PROCESS, new HeaderProcess()));
	_stateMap.insert(std::make_pair(BODY_PROCESS, new BodyProcess()));
}

HandleReq::HandleReq(Event *event): _event(event)
{
	_state = _event->getReqState();
	_stateMap.insert(std::make_pair(HEADER_PROCESS, new HeaderProcess()));
	_stateMap.insert(std::make_pair(BODY_PROCESS, new BodyProcess()));
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
	_state = event->getReqState();
}

bool HandleReq::handle(void)
{
	bool	keepHandling;

	keepHandling = true;
	while (keepHandling)
		keepHandling = _changeState(_handleState(_state));

	// maybe for remove and just turn void function
	return (0);
}

void HandleReq::setState(StateType state)
{
	_state = state;
}

bool HandleReq::_changeState(StateType state)
{
	bool change;

	if (_state == state)
		change = false;
	else 
		change = true;
	_state = state;
	_event->setReqState(state);
	return (change);
}

StateType HandleReq::_handleState(StateType state)
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
