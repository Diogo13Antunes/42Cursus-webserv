#pragma once

#include <string>
#include <iostream>
#include "IStateRes.hpp"
#include "StringUtils.hpp"
#include "TimeDate.hpp"
#include "HttpHeaderBuilder.hpp"

class CgiResponseProcess: public IStateRes
{
	private:
		std::map<std::string, std::string>	_getHeaderMap(std::string &src);
		std::string							_getKey(std::string &line);
		std::string							_getValue(std::string &line);
		bool								_existContent(std::map<std::string, std::string> &header);
		std::string							_getCgiBody(std::string &src);
		std::pair<std::string, std::string>	_makePair(std::string &line);

	public:
		CgiResponseProcess(void);
		~CgiResponseProcess(void);

		StateResType handle(Event *event, ServerConfig& configsData);
};
