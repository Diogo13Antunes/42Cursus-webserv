/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:06:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/29 17:27:14 by dsilveri         ###   ########.fr       */
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
