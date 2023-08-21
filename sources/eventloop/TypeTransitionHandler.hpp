/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTransitionHandler.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:00:56 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/25 16:28:41 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"

class TypeTransitionHandler: public IEventHandler
{
	private:

	public:
		TypeTransitionHandler(void);
		~TypeTransitionHandler(void);

		void handleEvent(Event *event);
		EventType getHandleType(void);
};
