#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define WHITE_SPACE "\r\n\t "

class MinificatorUtils
{
	public:

	static std::string	getFileContent(const char *file);
	static std::string	stringTrim(const std::string &src);
	static void			removeNewLineChars(std::string &src);
	static void			removeComentsWithDelemiters(std::string &src, const std::string delimiterBegin, const std::string delimiterEnd);
	static void			removeInlineComents(std::string &src, std::string commentDelimiter);

};
