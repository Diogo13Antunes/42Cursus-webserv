/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:54:59 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 10:26:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"
#include "HandleReq.hpp"
#include "configs.hpp"

class ReadHandler: public IEventHandler
{
	private:
		HandleReq	*_handleReq;
		char		_buffer[SOCKET_READ_BUFF_SIZE];

	public:
		ReadHandler(HandleReq *handleReq);
		~ReadHandler(void);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
