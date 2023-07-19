#include "RequestParser.hpp"
#include "StringUtils.hpp"

static std::vector<std::string>	getElementValue(const std::string &src);
static bool						isValidNumberOfQuotes(const std::string &src);
static std::string				getReadyValue(const std::string &src, size_t index1, size_t index2);

RequestParser::RequestParser(void) {}

RequestParser::~RequestParser(void) {}

void	RequestParser::headerParse(std::string &header)
{
	std::istringstream	iss(header);
	std::string			line;
	bool				isFirstLine = true;

	while (std::getline(iss, line))
	{
		line += "\n";
		if (line.find_first_not_of("\r\n") == line.npos)
			break;
		if (isFirstLine)
		{
			_requestLine = StringUtils::stringTrim(line);
			isFirstLine = false;
		}
		else
			_requestHeader.insert(_getHeaderFieldPair(line));
	}
	if (isValidHeader() != true || checkContentLenght() != true)
		throw BadRequestException();
}

void	RequestParser::bodyParse(std::string &body)
{
	_requestBody = body;
}

bool	RequestParser::isValidHeader(void)
{
	std::map<std::string, std::vector<std::string> >::iterator	it;
	std::string													key;

	for (it = _requestHeader.begin(); it != _requestHeader.end(); it++)
	{
		key = (*it).first;
		if (StringUtils::isStringEmptyOrSpaces(key))
			return (false);
	}
	return (true);
}

static std::string	getRequestLineMethod(std::string requestLine)
{
	std::string	res;
	size_t		index;

	index = requestLine.find_first_of(WHITE_SPACE);
	if (index != requestLine.npos)
		res = requestLine.substr(0, index);
	return (res);
}

bool	RequestParser::checkContentLenght(void)
{
	std::string	method;
	int			contentLen = 0;

	method = getRequestLineMethod(_requestLine);
	if (method.empty())
		return (false);

	contentLen = _getContentLen();
	if (contentLen == -1 && !method.compare("POST"))
		return (false);

	return (true);
}

std::string RequestParser::getRequestLine(void)
{
	return (_requestLine);
}

std::string RequestParser::getRequestBody(void)
{
	return (_requestBody);
}

std::map<std::string, std::vector<std::string> >	RequestParser::getRequestHeader(void)
{
	return (_requestHeader);
}

/* Exceptions */

const char *RequestParser::EmptyRequestException::what(void) const throw()
{
	return ("EmptyRequestException: Request file is empty");
}

const char *RequestParser::BadRequestException::what(void) const throw()
{
	return ("BadRequestException: Bad Request");
}

/* Class Private Functions */

int	RequestParser::_getContentLen(void)
{
	std::map<std::string, std::vector<std::string> >::iterator	it;
	int	len = -1;

	it = _requestHeader.find("content-length");
	if (it != _requestHeader.end())
	{
		if ((*it).second.size() == 1)
			len = std::atoi((*it).second.at(0).c_str());
	}
	return (len);
}

std::pair<std::string, std::vector<std::string> >	RequestParser::_getHeaderFieldPair(std::string &src)
{
	std::string					key;
	std::vector<std::string>	value;
	std::string					temp;
	size_t						index;

	index = src.find_first_of(":");
	if (index != src.npos)
	{
		if (src.find_last_not_of(WHITE_SPACE, index - 1) != src.npos)
		{
			key = src.substr(0, index);
			StringUtils::stringToLower(key);
		}
		if (src.find_first_not_of(WHITE_SPACE, index + 1) != src.npos)
		{
			temp = src.substr(src.find_first_of(":") + 1, src.size());
			temp = StringUtils::stringTrim(temp);
			value = getElementValue(temp);
		}
	}
	return (std::make_pair(key, value));
}

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
