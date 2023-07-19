#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <set>
#include <sstream>

#include "Terminal.hpp"

class RequestParser
{
	private:
		std::string											_requestLine;
		std::map<std::string, std::vector<std::string> >	_requestHeader;
		std::string											_requestBody;

		int													_getContentLen(void);
		std::pair<std::string, std::vector<std::string> >	_getHeaderFieldPair(std::string &src);

	public:
		RequestParser(void);
		~RequestParser(void);

		std::string											getRequestLine(void);
		std::string 										getRequestBody(void);
		std::map<std::string, std::vector<std::string> >	getRequestHeader(void);

		void												headerParse(std::string	&header);
		void												bodyParse(std::string &body);

		bool												isValidHeader(void);
		bool												checkContentLenght(void);

		class EmptyRequestException: public std::exception
		{
			public:
				const char *what() const throw();
		};

		class BadRequestException: public std::exception
		{
			public:
				const char *what() const throw();
		};
};
