/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:26 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/09 10:46:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

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

		int			getFd(void);
		short		getState(void);
		std::string	getResponse(void);

		void	setState(short state);
		void	setResponse(std::string	res);
};
