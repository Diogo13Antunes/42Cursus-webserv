/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMessengerClient.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:20:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/29 17:21:39 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//#include "Messenger.hpp"

#include "Message.hpp"

class Messenger;

typedef enum
{
    CONNECTIONS_ID,
    EVENTLOOP_ID,
	EVENTDEMUX_ID
}	ClientID;

/*
typedef struct s_msg
{
	ClientID	dst;
	int			fd;
	short		event;
	short		type;
}	t_msg;
*/

class AMessengerClient
{
	private:
		Messenger	*_messenger;
		ClientID	clientID;

	public:
		
		AMessengerClient(void);
		AMessengerClient(Messenger *messenger);
		AMessengerClient(const AMessengerClient &src);
		virtual ~AMessengerClient(void);
		AMessengerClient &operator=(const AMessengerClient &src);
		
		void				setMessenger(Messenger *messenger);
		void				sendMessage(Message *msg);
		
		virtual	ClientID	getId(void) = 0;
		virtual	void		receiveMessage(Message *msg) = 0;
};
