/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Timer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:23:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/08 14:18:16 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Timer.hpp"

time_t Timer::getActualTimeStamp(void)
{
	return (time(NULL));
}

bool Timer::isTimeoutExpired(time_t savedTime, int timeoutSec)
{
	time_t	timePassed;

	timePassed = time(NULL) - savedTime;
	if(timePassed >= timeoutSec)
		return (true);
	return (false);
}
