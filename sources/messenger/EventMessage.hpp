/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:49:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 10:52:58 by dsilveri         ###   ########.fr       */
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
		EventMessage(int dst, int fd, short event);
		EventMessage(const EventMessage &src);
		~EventMessage(void);
		EventMessage &operator=(const EventMessage &src);
		
		int		getFd(void);
		short	getEvent(void);	
};
