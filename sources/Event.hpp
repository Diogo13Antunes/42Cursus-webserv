/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:26 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/19 16:14:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "IEventHandler.hpp"
#include "Connection.hpp"

class Event
{
	private:
		std::string	_req;
		std::string	_res;
		Connection	*conn;

	public:
		Event(void);
		Event(const Event &src);
		~Event(void);
		Event &operator=(const Event &src);
};
