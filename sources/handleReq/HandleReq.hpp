/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleReq.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:15:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/23 14:49:07 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include "Event.hpp"
#include "StateType.hpp"
#include "IState.hpp"
#include "HeaderGetData.hpp"
#include "HeaderProcess.hpp"



class HandleReq 
{
    private:
		std::map<StateType, IState*>	_stateMap;
		StateType						_state;
		Event							*_event;

		bool _changeState(StateType state);
		StateType _handleState(StateType state);

    public:
		HandleReq(void);
		HandleReq(Event *event);
		~HandleReq(void);

		void setState(StateType state);
		bool handle(void);	
};
