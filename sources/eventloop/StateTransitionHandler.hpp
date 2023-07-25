/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateTransitionHandler.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:00:56 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/22 15:07:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"

class StateTransitionHandler: public IEventHandler
{
	private:

	public:
		StateTransitionHandler(void);
		~StateTransitionHandler(void);

		void handleEvent(Event *event);
		EventType getHandleType(void);
};
