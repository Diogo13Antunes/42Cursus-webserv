#include "RequestParserUtils.hpp"

static std::pair<std::string, std::string>	getPair(std::string &src);
static std::string							stringTrim(const std::string &str);

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
	line.erase(line.find_first_of("\r\n"));
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

std::map<std::string, std::string>	RequestParserUtils::getRequestHeader(std::vector<std::string> &src)
{
	std::map<std::string, std::string>	header;
	std::string	temp;

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
		if (src.at(i).find_first_not_of("\r\n") == src.at(i).npos)
			start_body = true;
	}
	return (body);
}

static std::pair<std::string, std::string>	getPair(std::string &src)
{
	std::string	key, value;

	key = src.substr(0, src.find_first_of(":"));
	for (size_t i = 0; i < key.size(); i++)
		key[i] = std::tolower(key[i]);
	value = src.substr(src.find_first_of(" "), src.size());
	value = stringTrim(value);
	return (std::make_pair(key, value));
}

static std::string	stringTrim(const std::string &str)
{
	std::string	trimmed = str;
	size_t		start = trimmed.find_first_not_of(WHITE_SPACE);
	size_t		end = trimmed.find_last_not_of(WHITE_SPACE);

	if (start != std::string::npos)
		trimmed = trimmed.substr(start);
	if (end != std::string::npos)
		trimmed = trimmed.substr(0, end);
	return (trimmed);
}
