/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IState.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:17:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 11:05:02 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Event.hpp"
#include "StateReqType.hpp"

class IState
{
    public:
    	virtual ~IState(void) {};

		virtual StateReqType handle(Event *event) = 0;
};
