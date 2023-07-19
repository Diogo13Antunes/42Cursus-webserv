/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:54:59 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/19 09:39:57 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <iostream>
#include <string>
#include <fstream>

#include "IEventHandler.hpp"
#include "RequestParser.hpp"
#include "RequestData.hpp"
#include "HandleReq.hpp"


#include "Configs.hpp"
#include "ConfigsData.hpp"

#define BUFF_SIZE1 100000

class ReadHandler: public IEventHandler
{
	private:

		HandleReq	*_handleReq;
		char		_buffer[BUFF_SIZE1];
		

	public:
		ReadHandler(void);
		ReadHandler(HandleReq *handleReq);
		~ReadHandler(void);
		ReadHandler(const ReadHandler &src);
		ReadHandler &operator=(const ReadHandler &src);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};