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

		std::string											_reqLineTarget;
		std::string											_reqLineHttpVersion;
		std::string											_reqLineMethod;
		std::string											_reqLinePath;

		std::string											_queryString;

		int													_statusCode;

		int													_isValidHeader(void);
		int													_getContentLen(void);
		std::pair<std::string, std::vector<std::string> >	_getHeaderFieldPair(std::string &src);
		int													_requestLineParser(void);
		int													_addHeaderElement(std::string &line);
		bool												_existAlreadyHeader(std::string &key);
		void												_requestTargetParser(void);
		int													_hasContentLengthAndTransferEncoded(void);
		int													_isValidRequestHeader(void);
		int													_isValidTransferEncodingValue(void);
		int													_isValidHost(void);
		int													_isValidContentLenght(void);

	public:
		RequestParser(void);
		~RequestParser(void);

		std::string											getRequestLine(void);
		std::map<std::string, std::vector<std::string> >	getRequestHeader(void);

		std::string											getReqLineTarget(void);
		std::string											getReqLineHttpVersion(void);
		std::string											getReqLineMethod(void);
		std::string											getReqLinePath(void);
		std::string											getConnectionField(void);
		std::vector<std::string>							getHeaderField(std::string fieldName);
		std::string											getQueryString(void);
		int													headerParse(std::string	&header);
};
