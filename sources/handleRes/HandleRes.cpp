/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:52:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/14 18:00:51 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <cstdlib> // para remover apenas de teste


#include <iostream>
#include <sys/socket.h>

#include "HandleRes.hpp"

HandleRes::HandleRes(void):
	_event(NULL),
	_state(CREATE_HEADER),
	_serverConf(NULL)
{
	_stateMap.insert(std::make_pair(CREATE_HEADER, new CreateHeaderState()));
	_stateMap.insert(std::make_pair(GET_BODY, new GetBodyState()));
	_stateMap.insert(std::make_pair(RESPONSE, new ResponseState()));
}

HandleRes::HandleRes(ConfigsData &configsData):
	_event(NULL),
	_configsData(configsData),
	_state(CREATE_HEADER), //maybe not nedded
	_serverConf(NULL)
{
	_stateMap.insert(std::make_pair(CREATE_HEADER, new CreateHeaderState()));
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

	_serverConf = _setServerConfig(_configsData.getServers());

	// For send data from cgi. Will be changed
	if (!_event->getCgiScriptResult().empty())
	{
		_event->setResState1(RESPONSE_END);
		send(_event->getFd(), _event->getCgiScriptResult().c_str(), _event->getCgiScriptResult().size(), 0);
	}
	else
	{	
		loop = true;
		while (loop && _event->getResState1() != RESPONSE_END)
		{
			if (_event->getResState1() == RESPONSE)
				loop = false;
			state = _handleState(_event->getResState1());
			_event->setResState1(state);
		}
	}
	//std::cout << "last State: " << state << std::endl;

	//exit(0);
}

StateResType HandleRes::_handleState(StateResType state)
{
	std::map<StateResType, IStateRes*>::iterator	it;

	if (state != RESPONSE_END)
	{
		it = _stateMap.find(state);
		if (it != _stateMap.end())
			//state = it->second->handle(_event, _configsData);
			state = it->second->handle(_event, *_serverConf);
	}
	return (state);
}

// Se returnar NULL deve responder 500 Internal error
ServerConfig* HandleRes::_setServerConfig(std::vector<ServerConfig>& serverConfigs)
{
	std::vector<ServerConfig>::iterator	it;
	std::string							ipReq;
	std::string							portReq;
	std::string							hostReq;
	ServerConfig						*serverConf;
	
	ipReq = _event->getIp();
	portReq = _event->getPort();
	hostReq = _event->getReqHost();
	serverConf = NULL;
	for (it = serverConfigs.begin(); it != serverConfigs.end(); it++)
	{
		if (!ipReq.compare(it->getIp()) && !portReq.compare(it->getPort()))
		{
			if (!hostReq.compare(it->getServerName()))
			{
				serverConf = &(*it);
				break ;
			}
			else if (serverConf == NULL)
				serverConf = &(*it);
		}
	}
	return (serverConf);
}

bool HandleRes::isResProcessingComplete(void)
{
	if (_event->getResState1() == RESPONSE_END)
		return (true);
	return (false);
}
