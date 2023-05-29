/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionMessage.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:49:45 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/29 15:57:35 by dsilveri         ###   ########.fr       */
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
		ConnectionMessage(ClientID dst, int fd);
		ConnectionMessage(const ConnectionMessage &src);
		~ConnectionMessage(void);
		ConnectionMessage &operator=(const ConnectionMessage &src);
		
		int	getFd(void);
};
