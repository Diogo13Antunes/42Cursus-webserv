/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:30 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 17:29:23 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"
#include "HandleRes.hpp"
#include "ConfigsData.hpp"

class WriteHandler: public IEventHandler
{
	private:
		HandleRes	*_handleRes;

	public:
		WriteHandler(HandleRes *handleRes);
		~WriteHandler(void);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
