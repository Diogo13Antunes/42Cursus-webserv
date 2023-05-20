/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Messenger.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:02:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/20 17:30:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include "IModule.hpp"

class Messenger
{
	private:
		std::map<ModuleID, IModule*> msgHandler;

	public:
		Messenger(void);
		Messenger(const Messenger &src);
		~Messenger(void);
		Messenger &operator=(const Messenger &src);

		void	registerModule(IModule *module);
		void	unregisterModule(IModule *module);
		void	sendMessage(t_msg msg);
};
