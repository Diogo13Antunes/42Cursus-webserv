/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 10:42:55 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Message
{
	private:
		int	_dst;

	public:
		Message(void);
		Message(int dst);
		Message(const Message &src);
		virtual ~Message(void);
		Message &operator=(const Message &src);

		int	getDst(void);
};
