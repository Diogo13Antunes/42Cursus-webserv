/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IState.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:17:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/23 12:54:02 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "StateType.hpp"

class IState
{
    public:
    	virtual ~IState(void) {};

		virtual StateType handle(void) = 0;
};