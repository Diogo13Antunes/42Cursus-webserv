#include "StringUtils.hpp"

#include <iostream>
#include <sstream>

std::string&	StringUtils::stringTrim(std::string &str)
{
	size_t		start;
	size_t		end;
	size_t		len;

	if (str.empty())
		return (str);
	start = str.find_first_not_of(WHITE_SPACE);
	end = str.find_last_not_of(WHITE_SPACE);
	if (start == str.npos || end == str.npos)
		str.clear();
	else
	{
		len = end - start + 1;
		str = str.substr(start, len);
	}
	return (str);
}

void	StringUtils::stringToLower(std::string &src)
{
	for (size_t i = 0; i < src.size(); i++)
		src[i] = std::tolower(src[i]);
}

bool	StringUtils::isStringEmptyOrSpaces(std::string str)
{
	if (!str.empty())
	{
		if (str.find_first_not_of(WHITE_SPACE) != str.npos)
			return (false);
	}
	return (true);
}

void	StringUtils::removeConsecutiveChars(std::string &src, char c)
{
    std::string output;
    bool 		lastWasChar = false;

	for (size_t i = 0; i < src.size(); i++)
	{
		if (src[i] == c && lastWasChar)
			continue;
		output.push_back(src[i]);
		lastWasChar = areCharsEqual(src[i], c);
	}
	src = output;
}

bool	StringUtils::areCharsEqual(char c1, char c2)
{
	if (c1 == c2)
		return (true);
	return (false);
}

bool	StringUtils::hasWhiteSpaces(std::string &str)
{
	if (str.find_first_of(WHITE_SPACE) != str.npos)
		return (true);
	return (false);
}

std::string StringUtils::toString(int num)
{
	std::stringstream ss;

	ss << num;
	return (std::string(ss.str()));
}