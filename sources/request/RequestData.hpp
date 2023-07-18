#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "RequestDataUtils.hpp"

#define REQUEST_METHOD			0
#define REQUEST_URL				1
#define REQUEST_HTTP_VERSION	2

class RequestData
{
	private:

		std::vector<std::string>							_requestLine;
		std::map<std::string, std::vector<std::string> >	_requestHeader;
		std::string											_requestBody;

		std::string											_requestPath;

		std::string											_queryString;

	public:
		RequestData(void);
		~RequestData(void);
		
		void												setRequestLine(std::string &src);
		void												setRequestHeader(std::map<std::string, std::vector<std::string> > &src);
		void												setRequestBody(std::string	&src);

		std::vector<std::string>							getRequestLine(void);
		std::map<std::string, std::vector<std::string> >	getRequestHeader(void);
		std::string											getRequestBody(void);
		std::string											getPath(void);
		size_t												getContentLenght(void);
		std::string											getQueryString(void);

		std::vector<std::string>							getHeaderValue(std::string	element);

		class InvalidRequestLineException: public std::exception
		{
			public:
				const char *what() const throw();
		};

};
