#pragma once

#include <string>
#include <sstream>

#define VALID_KEY_LETTERS	"abcdefghijklmnopqrstuvwxyz_-"
#define WHITE_SPACE			"\n\t\r "

class ConfigsUtils
{
	public:

		static std::string	stringTrim(const std::string &str);
		static bool			isValidArray(std::string &array);
		static bool			isInsideQuotes(std::string src, size_t index);
		static bool			isValisNbrQuotes(std::string &data);
		static int			strToInt(std::string str);
		static bool			isSingleColon(std::string &line);
		static std::string	removeQuotes(std::string src);
};
