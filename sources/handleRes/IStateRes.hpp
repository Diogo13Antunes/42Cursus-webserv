/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IStateRes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:17:19 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/29 12:06:50 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Event.hpp"
#include "StateResType.hpp"

class IStateRes
{
	public:
		virtual ~IStateRes(void) {};
		virtual StateResType handle(Event *event) = 0;
};
