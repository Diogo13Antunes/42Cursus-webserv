/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:49:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/29 15:57:30 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Message.hpp"

class EventMessage: public Message
{
	private:
		int		_fd;
		short	_event;
		
	public:
		EventMessage(void);
		EventMessage(ClientID dst, int fd, short event);
		EventMessage(const EventMessage &src);
		~EventMessage(void);
		EventMessage &operator=(const EventMessage &src);
		
		int		getFd(void);
		short	getEvent(void);	
};
