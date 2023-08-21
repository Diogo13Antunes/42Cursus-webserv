/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:49 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 13:51:39 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IState.hpp"

class BodyProcess: public IState
{
	public:
		BodyProcess(void);
		~BodyProcess(void);

		StateReqType handle(Event *event);
};
