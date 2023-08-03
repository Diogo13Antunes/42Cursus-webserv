/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkedBodyProcess.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:19:13 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/03 14:19:32 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IState.hpp"

class ChunkedBodyProcess: public IState
{
	private:
		int _hexToDec(std::string hex);

	public:
		ChunkedBodyProcess(void);
		~ChunkedBodyProcess(void);

		StateType handle(Event *event);
};
