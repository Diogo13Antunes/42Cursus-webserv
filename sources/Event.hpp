/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:26 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/22 17:55:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
//#include "IEventHandler.hpp"
#include "Connection.hpp"

class Event
{
	private:
		std::string	_req;
		std::string	_res;
		int			_fd;
		short		_state;

	public:
		Event(void);
		Event(int fd, int state);
		Event(const Event &src);
		~Event(void);
		Event &operator=(const Event &src);

		int		getFd(void);
		short	getState(void);

		void	setState(short state);
};
