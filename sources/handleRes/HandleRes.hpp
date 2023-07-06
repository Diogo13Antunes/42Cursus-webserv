/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:52:12 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/26 16:48:17 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Event.hpp"
#include "ConfigsData.hpp"

class HandleRes
{
	public:
		HandleRes(void);
		HandleRes(const HandleRes &src);
		~HandleRes(void);
		HandleRes &operator=(const HandleRes &src);

		void handle(Event *event, ConfigsData confData);
		bool isProcessingComplete(Event *event);

};
