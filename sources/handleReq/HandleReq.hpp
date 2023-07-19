/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleReq.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:15:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/19 16:43:52 by dsilveri         ###   ########.fr       */
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
		Event							*_event;

		bool		_changeState(StateType newState);
		StateType	_handleCurrentState(StateType state);
		
    public:
		HandleReq(void);
		~HandleReq(void);

		void	setEvent(Event *event);
		void	handle(void);	
		bool	isProcessingComplete(void);
};