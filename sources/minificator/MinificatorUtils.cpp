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

static std::vector<std::string>	getFileInVector(std::string src);
static std::string				stringWithoutComments(std::string src, std::string delimiter);
static bool						isStringEmpty(std::string src);

void	MinificatorUtils::removeInlineComents(std::string &src, std::string commentDelimiter)
{
	std::string					result;
	std::vector<std::string>	tempVector;
	std::string					line;

	tempVector = getFileInVector(src);
	for (size_t i = 0; i < tempVector.size(); i++)
	{
		line = stringWithoutComments(tempVector[i], commentDelimiter);
		if (!isStringEmpty(line))
			result += line;
	}
	src = result;
}

static std::vector<std::string>	getFileInVector(std::string src)
{
	std::vector<std::string>	result;
	std::string					line;
	std::size_t					pos = 0;
	std::size_t					end;

	while ((end = src.find('\n', pos)) != src.npos)
	{
        line = src.substr(pos, end - pos + 1);
		result.push_back(line);
        pos = end + 1;
    }
	return (result);
}

static bool	isInsideQuotes(std::string src, std::size_t index);

static std::string	stringWithoutComments(std::string src, std::string delimiter)
{
	std::string result;
	std::size_t	index = 0;
	std::size_t	end;

	while (1)
	{
		end = src.find(delimiter, index);
		if (end == src.npos)
			break;
		if (!isInsideQuotes(src, end))
		{
			if (end != 0)
			{
				result = src.substr(0, end) + "\n";
				if (isStringEmpty(result))
					result.clear();
			}
			return (result);
		}
		index = end + 2;
	}
	return (src);
}

static bool	isInsideQuotes(std::string src, std::size_t index)
{
	std::size_t	nbrQuotes = 0;

	if (index == 0)
		return (false);
	for (size_t i = 0; i < index; i++)
	{
		if (src[i] == '\"')
			nbrQuotes++;
	}
	if (nbrQuotes % 2 != 0 && nbrQuotes != 0)
		return (true);
	return (false);
}

static bool	isStringEmpty(std::string src)
{
	if (src.find_first_not_of(WHITE_SPACE) == src.npos)
		return (true);
	return (false);
}