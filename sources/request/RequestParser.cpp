#include "RequestParser.hpp"

RequestParser::RequestParser(void)
{
	/* std::vector<std::string>	requestContentVec;
	std::string					fileData;
	
	fileData = RequestParserUtils::getDataString(RequestFd);
	if (fileData.empty())
		throw EmptyRequestException();
	requestContentVec = RequestParserUtils::getDataVector(fileData);
	_requestLine = RequestParserUtils::getRequestLine(requestContentVec);
	_requestHeader = RequestParserUtils::getRequestHeader(requestContentVec);
	_requestBody = RequestParserUtils::getBody(requestContentVec); */
}

RequestParser::~RequestParser(void)
{
	//Default RequestParser Destructor
}

void	RequestParser::headerParse(std::string &header)
{
	std::vector<std::string>	requestHeaderVec;

	requestHeaderVec = RequestParserUtils::getDataVector(header);
	_requestLine = RequestParserUtils::getRequestLine(requestHeaderVec);
	_requestHeader = RequestParserUtils::getRequestHeader(requestHeaderVec);
}

void	RequestParser::bodyParse(std::string &body)
{
	_requestBody = body;
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
