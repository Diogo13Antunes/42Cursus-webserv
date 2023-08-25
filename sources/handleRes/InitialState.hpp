/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:48 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/24 17:53:17 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

class InitialState: public IStateRes
{
	public:
		InitialState(void);
		~InitialState(void);

		StateResType handle(Event *event, ServerConfig config);
};
