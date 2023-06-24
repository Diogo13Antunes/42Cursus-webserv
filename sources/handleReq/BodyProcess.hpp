/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyProcess.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:49:49 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/24 15:51:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IState.hpp"

class BodyProcess: public IState
{
	public:
		BodyProcess(void);
		BodyProcess(const BodyProcess &src);
		~BodyProcess(void);
		BodyProcess &operator=(const BodyProcess &src);

		StateType handle(Event *event);
};
