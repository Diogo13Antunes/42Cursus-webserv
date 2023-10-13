/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkedBodyProcess.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:19:13 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/23 15:01:55 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IState.hpp"

class ChunkedBodyProcess: public IState
{
	private:
		size_t _hexToDec(std::string hex);

	public:
		ChunkedBodyProcess(void);
		~ChunkedBodyProcess(void);

		StateReqType handle(Event *event, ConfigsData *configsData);
};
