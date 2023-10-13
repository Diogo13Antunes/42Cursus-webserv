/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadSocketHandler.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:54:59 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 18:54:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"
#include "HandleReq.hpp"
#include "configs.hpp"

class ReadSocketHandler: public IEventHandler
{
	private:
		HandleReq	*_handleReq;
		char		_buffer[SOCKET_READ_BUFF_SIZE];

		bool		_isHttps(Event *event);

	public:
		ReadSocketHandler(HandleReq *handleReq);
		~ReadSocketHandler(void);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
