/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleReq.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:15:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/10 17:17:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include "Event.hpp"
#include "StateReqType.hpp"
#include "IState.hpp"
#include "ConfigsData.hpp"

class HandleReq
{
    private:
		std::map<StateReqType, IState*>	_stateMap; 
		Event							*_event;
		ConfigsData						*_configsData;

		bool			_changeState(StateReqType newState);
		StateReqType	_handleCurrentState(StateReqType state);

    public:
		HandleReq(ConfigsData *configsData);
		~HandleReq(void);

		void	setEvent(Event *event);
		void	handle(void);	
		bool	isProcessingComplete(void);
};
