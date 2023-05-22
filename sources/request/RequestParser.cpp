#include "RequestParser.hpp"

RequestParser::RequestParser(int RequestFd)
{
	std::string	fileData = RequestParserUtils::getDataString(RequestFd);
	if (fileData.empty())
		throw EmptyRequestException();

	_requestContentVec = RequestParserUtils::getDataVector(fileData);
	/* for (size_t i = 0; i < _requestContentVec.size(); i++)
	{
		std::cout << _requestContentVec.at(i);
	} */

	_requestLine = RequestParserUtils::getRequestLine(_requestContentVec);
	_requestHeader = RequestParserUtils::getRequestHeader(_requestContentVec);
	_requestBody = RequestParserUtils::getBody(_requestContentVec);
	std::cout << "Line = " << _requestLine << std::endl;

	std::cout << "[KEY] | [VALUE]" << std::endl;
	std::map<std::string, std::string>::iterator	it;
	for (it = _requestHeader.begin(); it != _requestHeader.end(); it++)
		std::cout << "[" << (*it).first << "] | [" << (*it).second << "]" << std::endl;
	
	// _requestBody.erase(_requestBody.find_last_not_of("\r\n"));

	// std::cout << "---------- BODY ----------";
	// std::cout << _requestBody;
	// std::cout << "Length 1 > " << _requestBody.length() << std::endl;
	// std::cout << "Length 2 > " << _requestHeader.find("content-length")->second << std::endl;
}

RequestParser::~RequestParser(void)
{
	//Default RequestParser Destructor
}

/* Exceptions */

const char *RequestParser::EmptyRequestException::what(void) const throw()
{
	return ("EmptyRequestException: Request file is empty");
}
