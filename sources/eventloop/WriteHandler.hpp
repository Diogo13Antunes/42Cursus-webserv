/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:30 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 11:17:09 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"

class WriteHandler: public IEventHandler
{
	public:
		WriteHandler &operator=(const WriteHandler &src);
		WriteHandler(const WriteHandler &src);
		WriteHandler(void);
		~WriteHandler(void);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
