/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messenger.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:02:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/29 16:33:59 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include "AMessengerClient.hpp"
#include "Message.hpp"

class Messenger
{
	private:
		std::map<ClientID, AMessengerClient*> _clients;

	public:
		Messenger(void);
		Messenger(const Messenger &src);
		~Messenger(void);
		Messenger &operator=(const Messenger &src);

		/*
		void	registerModule(IModule *module);
		void	unregisterModule(IModule *module);
		void	sendMessage(t_msg msg);
		*/
		void	registerClient(AMessengerClient *client);
		void	unregisterClient(ClientID clientID);
		void	sendMessage(Message *msg);
};
