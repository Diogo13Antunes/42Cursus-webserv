/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/15 11:45:49 by dsilveri         ###   ########.fr       */
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
		Message(const Message& other);
		~Message(void);
		Message& operator=(const Message& other);

		int			getDst(void) const;
		int			getFd(void) const;
		MessageType	getType(void) const;
};
