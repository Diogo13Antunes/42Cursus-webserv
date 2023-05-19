/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:26 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/19 19:37:09 by dsilveri         ###   ########.fr       */
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
		Connection	*_conn;

	public:
		Event(void);
		Event(Connection *conn);
		Event(const Event &src);
		~Event(void);
		Event &operator=(const Event &src);

		int getFd(void);
};
