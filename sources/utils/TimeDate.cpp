/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TimeDate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:28:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/06 12:28:18 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TimeDate.hpp"

#include <iostream>
#include <sstream>


//Thu, 06 Jul 2023 10:21:09 GMT
std::string TimeDate::getTimeDateIMFfixdateFormat(void)
{
	std::string	IMFfixdate;
	time_t		now;
	struct tm	*gmt;

	now = time(NULL);
	gmt = gmtime(&now);
	IMFfixdate = _getDayOfWeekToString(gmt->tm_wday) + ", ";
	IMFfixdate += _getMonthDayToString(gmt->tm_mday) + " ";
	IMFfixdate += _getMonthToString(gmt->tm_mon) + " ";
	IMFfixdate += _getYearToString(gmt->tm_year) + " ";
	IMFfixdate += _getHourToString(gmt->tm_hour) + ":";
	IMFfixdate += _getMinToString(gmt->tm_min) + ":";
	IMFfixdate += _getSecToString(gmt->tm_sec) + " ";
	IMFfixdate += "GMT";
	return (IMFfixdate);
}

std::string TimeDate::getTimeDateIMFfixdateFormat(struct tm *timeDate)
{
	std::string	IMFfixdate;

	IMFfixdate = _getDayOfWeekToString(timeDate->tm_wday) + ", ";
	IMFfixdate += _getMonthDayToString(timeDate->tm_mday) + " ";
	IMFfixdate += _getMonthToString(timeDate->tm_mon) + " ";
	IMFfixdate += _getYearToString(timeDate->tm_year) + " ";
	IMFfixdate += _getHourToString(timeDate->tm_hour) + ":";
	IMFfixdate += _getMinToString(timeDate->tm_min) + ":";
	IMFfixdate += _getSecToString(timeDate->tm_sec) + " ";
	IMFfixdate += "GMT";
	return (IMFfixdate);
}

std::map<int, std::string>& TimeDate::_getDayMap(void)
{
	static std::map<int, std::string>	day;

	if (day.empty())
	{
		day.insert(std::make_pair(0, "Sun"));
		day.insert(std::make_pair(1, "Mon"));
		day.insert(std::make_pair(2, "Tue"));
		day.insert(std::make_pair(3, "Wed"));
		day.insert(std::make_pair(4, "Thu"));
		day.insert(std::make_pair(5, "Fri"));
		day.insert(std::make_pair(6, "Sat"));
	}
	return (day);
}

std::map<int, std::string>& TimeDate::_getMonMap(void)
{
	static std::map<int, std::string>	mon;

	if (mon.empty())
	{
		mon.insert(std::make_pair(0, "Jan"));
		mon.insert(std::make_pair(1, "Feb"));
		mon.insert(std::make_pair(2, "Mar"));
		mon.insert(std::make_pair(3, "Apr"));
		mon.insert(std::make_pair(4, "May"));
		mon.insert(std::make_pair(5, "Jun"));
		mon.insert(std::make_pair(6, "Jul"));
		mon.insert(std::make_pair(7, "Aug"));
		mon.insert(std::make_pair(8, "Sep"));
		mon.insert(std::make_pair(9, "Oct"));
		mon.insert(std::make_pair(10, "Nov"));
		mon.insert(std::make_pair(11, "Dec"));
	}
	return (mon);
}

std::string TimeDate::_getDayOfWeekToString(int wday)
{
	std::map<int, std::string>::iterator	it;
	std::map<int, std::string>				day;
	std::string								dayStr;

	day = _getDayMap();
	it = day.find(wday);
	if (it != day.end())
		dayStr = it->second;
	return (dayStr);
}

std::string TimeDate::_getMonthToString(int mon)
{
	std::map<int, std::string>::iterator	it;
	std::map<int, std::string>				month;
	std::string								monthStr;

	month = _getMonMap();
	it = month.find(mon);
	if (it != month.end())
		monthStr = it->second;
	return (monthStr);
}

std::string TimeDate::_getMonthDayToString(int mday)
{
	std::stringstream	monthDay;

	if (mday < 10)
		monthDay << "0";
	monthDay << mday;
	return (monthDay.str());
}

std::string TimeDate::_getYearToString(int year)
{
	std::stringstream	yearStr;

	yearStr << year + 1900;
	return (yearStr.str());
}

std::string TimeDate::_getHourToString(int hour)
{
	std::stringstream	hourStr;

	if (hour < 10)
		hourStr << "0";
	hourStr << hour;
	return (hourStr.str());
}

std::string TimeDate::_getMinToString(int min)
{
	std::stringstream	minStr;

	if (min < 10)
		minStr << "0";
	minStr << min;
	return (minStr.str());
}

std::string TimeDate::_getSecToString(int sec)
{
	std::stringstream	secStr;

	if (sec < 10)
		secStr << "0";
	secStr << sec;
	return (secStr.str());
}
