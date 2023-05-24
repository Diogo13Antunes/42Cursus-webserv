#include "RequestParser.hpp"

RequestParser::RequestParser(int RequestFd)
{
	std::string	fileData = RequestParserUtils::getDataString(RequestFd);
	if (fileData.empty())
		throw EmptyRequestException();
	_requestContentVec = RequestParserUtils::getDataVector(fileData);
	_requestLine = RequestParserUtils::getRequestLine(_requestContentVec);
	_requestHeader = RequestParserUtils::getRequestHeader(_requestContentVec);
	_requestBody = RequestParserUtils::getBody(_requestContentVec);
}

RequestParser::~RequestParser(void)
{
	//Default RequestParser Destructor
}

std::string RequestParser::getRequestLine(void)
{
	return (_requestLine);
}

std::string RequestParser::getRequestBody(void)
{
	return (_requestBody);
}

std::map<std::string, std::string>	RequestParser::getRequestHeader(void)
{
	return (_requestHeader);
}

/* Exceptions */

const char *RequestParser::EmptyRequestException::what(void) const throw()
{
	return ("EmptyRequestException: Request file is empty");
}
