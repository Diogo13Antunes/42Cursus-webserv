/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectionMessage.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:49:45 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/09 11:45:14 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Message.hpp"

typedef enum 
{
    NEW_CONNECTION,
    PROCESSING,
    PAUSED,
    CLOSE_CONNECTION
} ConnectionAction;


class ConnectionMessage: public Message
{
	private:
		int	_fd;
		ConnectionAction _state;

	public:
		ConnectionMessage(void);
		ConnectionMessage(int dst, int fd, ConnectionAction state);
		ConnectionMessage(const ConnectionMessage &src);
		~ConnectionMessage(void);
		ConnectionMessage &operator=(const ConnectionMessage &src);
		
		int					getFd(void);
		ConnectionAction	getState(void);
};
