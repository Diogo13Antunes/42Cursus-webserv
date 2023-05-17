/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:30 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/17 17:30:33 by dsilveri         ###   ########.fr       */
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

		void		handleEvent(void);
		EventType	getHandleType(void);
};
