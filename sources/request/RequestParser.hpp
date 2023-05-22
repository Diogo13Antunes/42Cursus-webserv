#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

#include "Terminal.hpp"
#include "RequestParserUtils.hpp"

class RequestParser
{
	private:
		std::vector<std::string>			_requestContentVec;
		std::string							_requestLine;
		std::map<std::string, std::string>	_requestHeader;
		std::string							_requestBody;

	public:
		RequestParser(int RequestFd);
		~RequestParser(void);
};
