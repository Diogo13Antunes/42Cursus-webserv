/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:52:12 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/14 10:15:23 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Event.hpp"
#include "StateResType.hpp"
#include "IStateRes.hpp"
#include "CreateHeaderState.hpp"
#include "GetBodyState.hpp"
#include "ResponseState.hpp"
#include "ServerConfig.hpp"

class HandleRes
{
	private:
		std::map<StateResType, IStateRes*>	_stateMap;
		ConfigsData							_configsData;
		ServerConfig						*_serverConf;
		Event								*_event;
		StateResType						_state;

		StateResType	_handleState(StateResType state);
		void			_setServerConfig(void);

	public:
		HandleRes(void);
		HandleRes(ConfigsData &configsData);
		~HandleRes(void);
		void setEvent(Event *event);

		void handle(void);
		bool isResProcessingComplete(void);
};
