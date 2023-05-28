/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messenger.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:02:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/27 15:39:04 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include "AMessengerClient.hpp"

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
		void	registerclient(AMessengerClient *client);
		void	unregisterclient(AMessengerClient *client);
		void	sendMessage(t_msg msg);
};
