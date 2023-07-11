/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:49:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/11 16:11:59 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Message.hpp"

typedef enum 
{
    NEW_EVENT,
    CHANGE_EVENT
} EventAction;

class EventMessage: public Message
{
	private:
		EventAction	_action;
		int			_fd;
		short		_event;

	public:
		EventMessage(void);
		EventMessage(int dst, int fd, short event, EventAction action);
		EventMessage(const EventMessage &src);
		~EventMessage(void);
		EventMessage &operator=(const EventMessage &src);
		
		int			getFd(void);
		short		getEvent(void);	
		EventAction	getAction(void);
};
