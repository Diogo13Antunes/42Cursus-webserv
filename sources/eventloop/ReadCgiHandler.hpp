/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadCgiHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:38:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/07 17:28:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"

#define BUFFER_CGI_READ_SIZE	10000

class ReadCgiHandler: public IEventHandler
{
	private:
		char	_buffer[BUFFER_CGI_READ_SIZE];

	public:
		ReadCgiHandler(void);
		~ReadCgiHandler(void);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
