#include "StringUtils.hpp"

#include <iostream>

std::string&	StringUtils::stringTrim(std::string &str)
{
	size_t		start;
	size_t		end;
	size_t		len;

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
