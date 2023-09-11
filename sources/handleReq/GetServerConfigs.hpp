/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetServerConfigs.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 08:53:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 08:58:28 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IState.hpp"

class GetServerConfigs: public IState
{
	public:
		GetServerConfigs(void);
		~GetServerConfigs(void);

		StateReqType handle(Event *event, ConfigsData *configsData);
};
