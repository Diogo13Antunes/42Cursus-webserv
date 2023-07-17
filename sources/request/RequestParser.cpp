#include "RequestParser.hpp"

RequestParser::RequestParser(void) {}

RequestParser::~RequestParser(void) {}

void	RequestParser::headerParse(std::string &header)
{
	std::vector<std::string>	requestHeaderVec;

	requestHeaderVec = RequestParserUtils::getDataVector(header);
	_requestLine = RequestParserUtils::getRequestLine(requestHeaderVec);
	_requestHeader = RequestParserUtils::getRequestHeader(requestHeaderVec);

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
		if (RequestParserUtils::isStringEmpty(key))
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
