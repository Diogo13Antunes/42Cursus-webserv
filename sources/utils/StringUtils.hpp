#pragma once

#include <string>

#define WHITE_SPACE		"\n\t\r "

class StringUtils
{
	public:
		static std::string&	stringTrim(std::string &str);
		static void			stringToLower(std::string &src);
		static bool			isStringEmptyOrSpaces(std::string str);

};
