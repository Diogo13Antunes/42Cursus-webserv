#include "ConfigsUtils.hpp"

std::string	ConfigsUtils::stringTrim(const std::string &str)
{
	std::string	trimmed = str;
	size_t		start = trimmed.find_first_not_of(WHITE_SPACE);
	size_t		end = trimmed.find_last_not_of(WHITE_SPACE);

	if (start != std::string::npos)
		trimmed = trimmed.substr(start);
	if (end != std::string::npos)
		trimmed = trimmed.substr(0, end + 1);
	return (trimmed);
}

bool	ConfigsUtils::isInsideQuotes(std::string src, size_t index)
{
	if (src.find_first_of('\"', index) == src.npos)
		return (false);
	if (src.find_last_of('\"', index) == src.npos)
		return (false);
	return (true);
}

bool	ConfigsUtils::isValidArray(std::string &array)
{
	size_t			nbrBrackets = 0;
	size_t			nbrQuotes = 0;
	std::string		temp;
	size_t			a = 1;

	for (size_t i = 0; i < array.size(); i++)
	{
		if (array[i] == '[')
			nbrBrackets++;
		else if (array[i] == ']')
			nbrBrackets--;
		else if (array[i] == '\"')
			nbrQuotes++;
	}
	if (nbrBrackets != 0 || nbrQuotes % 2 != 0)
		return (false);
	while (array[a])
	{
		while (array[a] != ',' && array[a + 1])
			temp += array[a++];
		if (temp.find_first_not_of(WHITE_SPACE) == temp.npos)
			return (false);
		temp.clear();
		a++;
	}
	return (true);
}

bool	ConfigsUtils::isValisNbrQuotes(std::string &data)
{
	size_t nbrQuotes = 0;

	for (size_t i = 0; i < data.size(); i++)
		if (data[i] == '\"')
			nbrQuotes++;
	if (nbrQuotes != 2)
		return (false);
	return (true);
}

int	ConfigsUtils::strToInt(std::string str)
{
	std::stringstream	out(str);
	int	res = 0;

	out >> res;

	return (res);
}

bool	ConfigsUtils::isSingleColon(std::string &line)
{
	int	count = 0;

	for (size_t i = 0; i < line.size(); i++)
		if (line[i] == ':' && !ConfigsUtils::isInsideQuotes(line, i))
			count++;
	if (count != 1)
		return (false);
	return (true);
}

std::string	ConfigsUtils::removeQuotes(std::string src)
{
	std::string	res;

	for (size_t i = 0; i < src.size(); i++)
	{
		if (src[i] != '\"')
			res += src[i];
	}
	return (res);
}

std::string	ConfigsUtils::removeComments(std::string src)
{
	std::string	result;

	result = src;
	for (size_t j = 0; j < result.size(); j++)
	{
		if (result[j] == '#')
		{
			if (!ConfigsUtils::isInsideQuotes(result, j))
				result = result.substr(0, j);
		}
	}
	if (result.find_first_not_of(WHITE_SPACE) == result.npos)
		result.clear();
	if (!result.empty())
		result = ConfigsUtils::stringTrim(result);
	return (result);
}
