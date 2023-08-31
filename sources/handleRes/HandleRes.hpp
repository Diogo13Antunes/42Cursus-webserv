/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:52:12 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/31 12:08:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Event.hpp"
#include "StateResType.hpp"
#include "IStateRes.hpp"
#include "ServerConfig.hpp"

class HandleRes
{
	private:
		std::map<StateResType, IStateRes*>	_stateMap;
		ConfigsData							*_configsData;
		ServerConfig						*_serverConf;
		Event								*_event;

		StateResType _handleState(StateResType state);

	public:
		HandleRes(ConfigsData *configsData);
		~HandleRes(void);

		void	setEvent(Event *event);
		void	handle(void);
		bool	isResProcessingComplete(void);
};
