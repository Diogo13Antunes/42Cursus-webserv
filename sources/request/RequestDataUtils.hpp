#pragma once

#include <string>
#include <iostream>
#include <vector> 

#define WHITE_SPACE		"\n\t\r "

class RequestDataUtils
{
	private:

	public:
		
		RequestDataUtils(void);
		~RequestDataUtils(void);

		static std::string	stringTrim(const std::string &str);
		static std::string	getRequestLineElement(const std::string &src, size_t i1, size_t i2);
		static bool			isValidRequestLine(std::vector<std::string> &requestLine);

};
