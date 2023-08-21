/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadCgiHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:38:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/25 18:03:45 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"

class ReadCgiHandler: public IEventHandler
{
	public:
		ReadCgiHandler(void);
		~ReadCgiHandler(void);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
