/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:49 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 08:40:50 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IState.hpp"

class BodyProcess: public IState
{
	public:
		BodyProcess(void);
		~BodyProcess(void);

		StateReqType handle(Event *event, ConfigsData *configsData);
};
