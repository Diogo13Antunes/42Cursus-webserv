/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteCgiHandler.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:39:29 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/25 17:46:57 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"

class WriteCgiHandler: public IEventHandler
{
	public:
		WriteCgiHandler(void);
		~WriteCgiHandler(void);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
