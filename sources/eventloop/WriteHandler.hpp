/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:30 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/26 12:08:45 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"
#include "ConfigsData.hpp"

class WriteHandler: public IEventHandler
{
	private:
		ConfigsData	_data;

	public:
		WriteHandler(void);
		WriteHandler(ConfigsData data);
		~WriteHandler(void);
		WriteHandler(const WriteHandler &src);
		WriteHandler &operator=(const WriteHandler &src);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
