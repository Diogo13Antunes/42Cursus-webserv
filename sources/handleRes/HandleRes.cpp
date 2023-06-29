/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:52:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/29 15:48:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> // para remover apenas de teste


#include <iostream>
#include <sys/socket.h>

#include "HandleRes.hpp"

HandleRes::HandleRes(void): _event(NULL)
{
	_stateMap.insert(std::make_pair(CREATE_HEADER, new CreateHeaderState()));
}

HandleRes::HandleRes(Event *event): _event(event)
{
	_stateMap.insert(std::make_pair(CREATE_HEADER, new CreateHeaderState()));	
}

HandleRes::HandleRes(const HandleRes &src)
{
	//HandleRes Copy Constructor
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

/*
HandleRes &HandleRes::operator=(const HandleRes &src)
{
	//HandleRes Copy Assignment Operator
}
*/

void HandleRes::setEvent(Event *event)
{
	_event = event;
}

void HandleRes::handle(void)
{
	_handleState(CREATE_HEADER);
	exit(0);
}

StateResType HandleRes::_handleState(StateResType state)
{
	std::map<StateResType, IStateRes*>::iterator	it;

	if (state != RESPONSE_END)
	{
		it = _stateMap.find(state);
		if (it != _stateMap.end())
			state = it->second->handle(_event);
	}
	return (state);
}