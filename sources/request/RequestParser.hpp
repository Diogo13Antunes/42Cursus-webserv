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
		std::string											_requestLine;
		std::map<std::string, std::vector<std::string> >	_requestHeader;
		std::string											_requestBody;

	public:
		RequestParser(int RequestFd);
		~RequestParser(void);

		std::string											getRequestLine(void);
		std::string 										getRequestBody(void);
		std::map<std::string, std::vector<std::string> >	getRequestHeader(void);

		class EmptyRequestException: public std::exception
		{
			public:
				const char *what() const throw();
		};

};
