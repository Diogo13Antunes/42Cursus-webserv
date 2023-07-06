/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TimeDate.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:28:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/06 12:19:14 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <ctime>
#include <map>

class TimeDate
{
	private:
		static std::map<int, std::string>&	_getDayMap(void);
		static std::map<int, std::string>&	_getMonMap(void);
		static std::string					_getDayOfWeekToString(int wday);
		static std::string					_getMonthToString(int mon);
		static std::string					_getMonthDayToString(int mday);
		static std::string					_getYearToString(int year);
		static std::string					_getHourToString(int hour);
		static std::string					_getMinToString(int min);
		static std::string					_getSecToString(int sec);

	public:
		static std::string getTimeDateIMFfixdateFormat(void);
		static std::string getTimeDateIMFfixdateFormat(struct tm *timeDate);
};
