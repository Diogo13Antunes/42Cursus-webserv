/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleReq.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:15:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/29 15:45:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include "Event.hpp"
#include "StateType.hpp"
#include "IState.hpp"
#include "HeaderProcess.hpp"
#include "BodyProcess.hpp"

class HandleReq 
{
    private:
		std::map<StateType, IState*>	_stateMap;
		StateType						_state; 	//to remove 
		Event							*_event;

		bool _changeState(StateType state);
		StateType _handleState(StateType state);

    public:
		HandleReq(void);
		HandleReq(Event *event);
		~HandleReq(void);

		void setEvent(Event *event);

		// for remove
		void setState(StateType state);
		
		bool handle(void);	

		bool isProcessingComplete(void);
};
