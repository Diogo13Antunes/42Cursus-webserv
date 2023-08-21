/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTransitionHandler.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:00:56 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/21 14:13:49 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"

class TypeTransitionHandler: public IEventHandler
{
	private:
		ConfigsData	*_configs;

		ServerConfig* _getServerConfig(Event *event, std::vector<ServerConfig>& serverConfigs);

	public:
		TypeTransitionHandler(ConfigsData *configs);
		~TypeTransitionHandler(void);

		void handleEvent(Event *event);
		EventType getHandleType(void);
};
