/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMessengerClient.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:20:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 10:32:53 by dsilveri         ###   ########.fr       */
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
