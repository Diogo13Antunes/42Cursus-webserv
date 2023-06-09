#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "RequestDataUtils.hpp"

class RequestData
{
	private:

		std::vector<std::string>							_requestLine;
		std::map<std::string, std::vector<std::string> >	_requestHeader;
		std::string											_requestBody;

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

		class InvalidRequestLineException: public std::exception
		{
			public:
				const char *what() const throw();
		};

};
