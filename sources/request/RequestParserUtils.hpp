#pragma once

#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <map>

#define BUFFER_SIZE		2048
#define WHITE_SPACE		"\n\t\r "

class RequestParserUtils
{
	public:
		
		static std::string										getRequestLine(std::vector<std::string> &src);
		static std::string										getDataString(int fd);
		static std::vector<std::string>							getDataVector(std::string &src);
		static std::map<std::string, std::vector<std::string> >	getRequestHeader(std::vector<std::string> &src);
		static std::string										getBody(std::vector<std::string> &src);

};
