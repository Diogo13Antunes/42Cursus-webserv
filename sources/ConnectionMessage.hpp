/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionMessage.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:49:45 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/30 08:47:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Message.hpp"

class ConnectionMessage: public Message
{
	private:
		int	_fd;

	public:
		ConnectionMessage(void);
		ConnectionMessage(int dst, int fd);
		ConnectionMessage(const ConnectionMessage &src);
		~ConnectionMessage(void);
		ConnectionMessage &operator=(const ConnectionMessage &src);
		
		int	getFd(void);
};
