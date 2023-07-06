#include "RequestParserUtils.hpp"

static std::vector<std::string>								getElementValue(const std::string &src);
static std::pair<std::string, std::vector<std::string> >	getPair(std::string &src);
static std::string											stringTrim(const std::string &str);

std::string	RequestParserUtils::getDataString(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	std::string	data;
	int			bytesRead;

	while (true)
	{
		std::memset(buff, 0, BUFFER_SIZE + 1);

		bytesRead = read(fd, buff, BUFFER_SIZE);
		if (bytesRead <= 0)
			break;
		data += buff;
	}
	return (data);
}

std::string	RequestParserUtils::getRequestLine(std::vector<std::string> &src)
{
	std::string	line;

	line = src.begin()->c_str();
	line = stringTrim(line);
	return (line);
}

std::vector<std::string>	RequestParserUtils::getDataVector(std::string &src)
{
	std::vector<std::string>	result;
	std::istringstream			iss(src);
	std::string					line;

	while (std::getline(iss, line))
		result.push_back(line + "\n");
	return (result);
}

std::map<std::string, std::vector<std::string> >	RequestParserUtils::getRequestHeader(std::vector<std::string> &src)
{
	std::map<std::string, std::vector<std::string> >	header;
	std::string											temp;

	for (size_t i = 1; i < src.size(); i++)
	{
		temp = src.at(i).c_str();
		if (temp.find_first_not_of("\r\n") == temp.npos)
			break;
		header.insert(getPair(temp));
	}
	return (header);
}

std::string	RequestParserUtils::getBody(std::vector<std::string> &src)
{
	std::string	body;
	bool		start_body = false;

	body.clear();
	for (size_t i = 1; i < src.size(); i++)
	{
		if (start_body)
			body += src.at(i).c_str();
		else if (src.at(i).find_first_not_of("\r\n") == src.at(i).npos)
			start_body = true;
	}
	return (body);
}

bool	RequestParserUtils::isStringEmpty(std::string str)
{
	if (!str.empty())
	{
		if (str.find_first_not_of(WHITE_SPACE) != str.npos)
			return (false);
	}
	return (true);
}

static std::pair<std::string, std::vector<std::string> >	getPair(std::string &src)
{
	std::string					key;
	std::vector<std::string>	value;
	std::string					temp;
	size_t		index;

	key.clear();
	value.clear();
	index = src.find_first_of(":");
	if (index != src.npos)
	{
		if (src.find_last_not_of(WHITE_SPACE, index - 1) != src.npos)
		{
			key = src.substr(0, index);
			for (size_t i = 0; i < key.size(); i++)
				key[i] = std::tolower(key[i]);
		}
		if (src.find_first_not_of(WHITE_SPACE, index + 1) != src.npos)
		{
			temp = src.substr(src.find_first_of(":") + 1, src.size());
			temp = stringTrim(temp);
			value = getElementValue(temp);
		}
	}
	return (std::make_pair(key, value));
}

static std::string	stringTrim(const std::string &str)
{
	std::string	trimmed;
	size_t		start;
	size_t		end;
	size_t		len;

	start = str.find_first_not_of(WHITE_SPACE);
	end = str.find_last_not_of(WHITE_SPACE);
	len = end - start + 1;
	trimmed = str.substr(start, len);
	return (trimmed);
}

static bool			isValidNumberOfQuotes(const std::string &src);
static std::string	getReadyValue(const std::string &src, size_t index1, size_t index2);

static std::vector<std::string>	getElementValue(const std::string &src)
{
	std::vector<std::string>	elements;
	std::string					temp;
	size_t						nbrQuotes = 0;
	size_t						j = 0;

	if (isValidNumberOfQuotes(src))
	{
		for (size_t i = 0; i < src.size(); i++)
		{
			if (src[i] == '\"')
				nbrQuotes++;
			if (i == src.size() - 1 || (src[i] == ',' && nbrQuotes % 2 == 0))
			{
				temp = getReadyValue(src, i, j);
				elements.push_back(temp);
				j = i + 1;
			}
		}
	}
	return (elements);
}

static bool	isValidNumberOfQuotes(const std::string &src)
{
	size_t	nbrQuotes = 0;

	for (size_t i = 0; i < src.size(); i++)
	{
		if (src[i] == '\"')
			nbrQuotes++;
	}
	if (nbrQuotes % 2 != 0)
		return (false);
	return (true);
}

static std::string	getReadyValue(const std::string &src, size_t index1, size_t index2)
{
	const std::string	notValueChars = "\n\r\t\", ";
	std::string			result;
	size_t				i1 = 0;
	size_t				i2 = 0;

	i1 = src.find_first_not_of(notValueChars, index2);
	i2 = src.find_last_not_of(notValueChars, index1);
	result = src.substr(i1, i2 - i1 + 1);
	return (result);
}
