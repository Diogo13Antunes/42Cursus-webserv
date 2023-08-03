/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:54:59 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/03 16:28:42 by dsilveri         ###   ########.fr       */
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

#define BUFF_SIZE1 1
//#define BUFF_SIZE1 2


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