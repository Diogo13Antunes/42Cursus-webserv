/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:52:12 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 17:42:40 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Event.hpp"
#include "StateResType.hpp"
#include "IStateRes.hpp"
#include "CreateHeaderState.hpp"
#include "GetBodyState.hpp"
#include "ResponseState.hpp"

class HandleRes
{
	private:
		std::map<StateResType, IStateRes*>	_stateMap;
		ConfigsData							_configsData;
		Event								*_event;
		StateResType						_state;

		StateResType _handleState(StateResType state);
	public:
		HandleRes(void);
		HandleRes(ConfigsData &configsData);
		~HandleRes(void);
		void setEvent(Event *event);

		void handle(void);
		bool isResProcessingComplete(void);
};
