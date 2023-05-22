#include "RequestParser.hpp"

RequestParser::RequestParser(int RequestFd)
{
	std::string	fileData = RequestParserUtils::getDataString(RequestFd);
	// if (fileData.empty())
		// mandar exception
	_requestContentVec = RequestParserUtils::getDataVector(fileData);
	// for (size_t i = 0; i < _requestContentVec.size(); i++)
	// {
	// 	std::cout << _requestContentVec.at(i);
	// }

	_requestLine = RequestParserUtils::getRequestLine(_requestContentVec);
	_requestHeader = RequestParserUtils::getRequestHeader(_requestContentVec);
	_requestBody = RequestParserUtils::getBody(_requestContentVec);
	std::cout << "Line = " << _requestLine << std::endl;
	
	std::cout << "[KEY] | [VALUE]" << std::endl;
	std::map<std::string, std::string>::iterator	it;
	for (it = _requestHeader.begin(); it != _requestHeader.end(); it++)
		std::cout << "[" << (*it).first << "] | [" << (*it).second << "]" << std::endl;
	
	std::cout << "---------- BODY ----------";
	std::cout << _requestBody;
}

RequestParser::~RequestParser(void)
{
	//Default RequestParser Destructor
}
