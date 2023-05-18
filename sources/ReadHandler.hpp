/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:54:59 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/18 12:08:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"

class ReadHandler: public IEventHandler
{
	public:
		ReadHandler &operator=(const ReadHandler &src);
		ReadHandler(const ReadHandler &src);
		ReadHandler(void);
		~ReadHandler(void);

		void		handleEvent(int event);
		EventType	getHandleType(void);
};
