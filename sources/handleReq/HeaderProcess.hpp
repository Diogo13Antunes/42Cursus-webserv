/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 11:06:25 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IState.hpp"

class HeaderProcess: public IState
{
	private:
		bool _isChunkedTransfer(Event *event);

	public:
		HeaderProcess(void);
		~HeaderProcess(void);
		
		StateReqType handle(Event *event);
};
