/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/29 15:15:51 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AMessengerClient.hpp"

class Message
{
	private:
		ClientID	_dst;

	public:
		Message(void);
		Message(ClientID dst);
		Message(const Message &src);
		virtual ~Message(void);
		Message &operator=(const Message &src);

		ClientID	getDst(void);
};
