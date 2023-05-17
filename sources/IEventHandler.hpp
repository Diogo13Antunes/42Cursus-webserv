/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEventHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:48:24 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/17 14:52:31 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class IEventHandler
{
	public:
		virtual ~IEventHandler(void) {};

		virtual void handleEvent(void) = 0;
		virtual void getHandleID(void) = 0; 
};
