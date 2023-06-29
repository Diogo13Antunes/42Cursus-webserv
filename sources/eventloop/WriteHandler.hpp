/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:30 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/29 16:42:34 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"
#include "HandleRes.hpp"


#include "ConfigsData.hpp"

class WriteHandler: public IEventHandler
{
	private:
		//ConfigsData	_data;
		HandleRes	*_handleRes;

	public:
		WriteHandler(void);
		WriteHandler(HandleRes *handleRes);
		//WriteHandler(ConfigsData data);
		~WriteHandler(void);
		WriteHandler(const WriteHandler &src);
		WriteHandler &operator=(const WriteHandler &src);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
