#include "MinificatorUtils.hpp"

std::string	MinificatorUtils::getFileContent(const char *file)
{
	std::fstream	fd;
	std::string		fileContent;
	std::string		temp;

	fd.open(file, std::ios::in);
	if (!fd.is_open())
		return (fileContent);
	while (std::getline(fd, temp))
		fileContent += temp + "\n";
	fd.close();
	return (fileContent);
}

std::string	MinificatorUtils::stringTrim(const std::string &str)
{
	std::string	trimmed;
	size_t		start;
	size_t		end;
	size_t		len;

	if (str.empty())
		return (str);
	start = str.find_first_not_of(WHITE_SPACE);
	end = str.find_last_not_of(WHITE_SPACE);
	len = end - start + 1;
	trimmed = str.substr(start, len);
	return (trimmed);
}

void	MinificatorUtils::removeComentsWithDelemiters(std::string &src, const std::string delimiterBegin, const std::string delimiterEnd)
{
	std::string result;
	size_t		start = 0;
	size_t		end = 0;
	size_t		index = 0;

	while (1)
	{
		start = src.find(delimiterBegin, index);
		end = src.find(delimiterEnd, start);
		if (start == src.npos || end == src.npos)
		{
			result += src.substr(index, src.size() - index + 1);
			break;
		}
		result += src.substr(index, start - index);
		index = end + delimiterEnd.size() + 1;
	}
	src = result;
}

void	MinificatorUtils::removeNewLineChars(std::string &src)
{
	std::string result;
	std::string	line;
	size_t		i = 0;
	size_t		j = 0;

	while (1)
	{
		i = src.find_first_of("\n", j);
		if (i == src.npos)
			break;
		line = src.substr(j, i - j);
		if (line.find_first_not_of(WHITE_SPACE) != line.npos)
			result += MinificatorUtils::stringTrim(line) + " ";
		i++;
		j = i;
	}
	src = result;
}

void	MinificatorUtils::removeSpacesOutsideQuotes(std::string &src)
{
	std::string	result;
	size_t		nbrQuotes = 0;

	for (size_t i = 0; i < src.size(); i++)
	{		
		if (src.at(i) == '\"')
			nbrQuotes++;
		if (!(src.at(i) == ' ' && nbrQuotes % 2 == 0))
			result += src.at(i);
	}
	src = result;
}
