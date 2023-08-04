/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleReq.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:15:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 11:05:17 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include "Event.hpp"
#include "StateReqType.hpp"
#include "IState.hpp"

class HandleReq
{
    private:
		std::map<StateReqType, IState*>	_stateMap; 
		Event							*_event;

		bool			_changeState(StateReqType newState);
		StateReqType	_handleCurrentState(StateReqType state);
		
    public:
		HandleReq(void);
		~HandleReq(void);

		void	setEvent(Event *event);
		void	handle(void);	
		bool	isProcessingComplete(void);
};
