/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IState.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:17:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 08:39:23 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Event.hpp"
#include "StateReqType.hpp"
#include "ConfigsData.hpp"

class IState
{
    public:
    	virtual ~IState(void) {};

		virtual StateReqType handle(Event *event, ConfigsData *configsData) = 0;
};
