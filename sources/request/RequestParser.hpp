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

		std::vector<std::string>							_implementedMethods;
		std::string											_requestLine;
		std::map<std::string, std::vector<std::string> >	_requestHeader;
		std::string											_requestBody;

		std::string											_reqLineTarget;
		std::string											_reqLineHttpVersion;
		std::string											_reqLineMethod;
		std::string											_reqLinePath;

		std::string											_queryString;

		int													_statusCode;

		int													_getContentLen(void);
		std::pair<std::string, std::vector<std::string> >	_getHeaderFieldPair(std::string &src);
		int													_requestLineParser(void);
		int													_addHeaderElement(std::string &line);
		void												_requestTargetParser(void);
		bool												_isImplementedRequestMethod(void);
		int													_hasContentLengthAndTransferEncoded(void);
		int													_isValidRequestHeader(void);
		bool												_isValidTransferEncodingValue(void);

	public:
		RequestParser(void);
		~RequestParser(void);

		std::string											getRequestLine(void);
		std::string 										getRequestBody(void);
		std::map<std::string, std::vector<std::string> >	getRequestHeader(void);

		std::string											getReqLineTarget(void);
		std::string											getReqLineHttpVersion(void);
		std::string											getReqLineMethod(void);
		std::string											getReqLinePath(void);
		std::vector<std::string>							getHeaderField(std::string fieldName);

		int													headerParse(std::string	&header);
		void												bodyParse(std::string &body);

		int													isValidHeader(void);
		int													checkContentLenght(void);

		class BadRequestException: public std::exception
		{
			public:
				const char *what() const throw();
		};

		class URITooLongException: public std::exception
		{
			public:
				const char *what() const throw();
		};

		class NotImplementedException: public std::exception
		{
			public:
				const char *what() const throw();
		};

};
