/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Timer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:23:40 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/08 14:09:07 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ctime>

class Timer
{
	public:
		static time_t	getActualTimeStamp(void);
		static bool		isTimeoutExpired(time_t savedTime, int timeoutSec);
};
