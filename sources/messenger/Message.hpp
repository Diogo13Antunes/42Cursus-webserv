/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/14 17:14:39 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "MessageType.hpp" 

class Message
{
	private:
		MessageType	_type;
		int			_dst;
		int			_fd;

	public:
		Message(int dst, int fd, MessageType type);
		~Message(void);

		int			getDst(void);
		int			getFd(void);
		MessageType	getType(void);
};
