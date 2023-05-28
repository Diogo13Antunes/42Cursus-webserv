/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMessengerClient.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:20:32 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/28 14:24:58 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//#include "Messenger.hpp"

class Messenger;

typedef enum
{
    CONNECTIONS_ID,
    EVENTLOOP_ID,
	EVENTDEMUX_ID
}	ClientID;

typedef struct s_msg
{
	ClientID	dst;
	int			fd;
	short		event;
	short		type;
}	t_msg;


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
		void				sendMessage(t_msg msg);
		
		virtual	ClientID	getId(void) = 0;
		virtual	void		receiveMessage(t_msg msg) = 0;
};
