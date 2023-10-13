/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteSocketHandler.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:30:30 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/21 11:52:20 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IEventHandler.hpp"
#include "HandleRes.hpp"
#include "ConfigsData.hpp"

class WriteSocketHandler: public IEventHandler
{
	private:
		HandleRes	*_handleRes;

	public:
		WriteSocketHandler(HandleRes *handleRes);
		~WriteSocketHandler(void);

		void		handleEvent(Event *event);
		EventType	getHandleType(void);
};
