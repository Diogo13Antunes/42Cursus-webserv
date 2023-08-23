#pragma once

#include <string>
#include <iostream>
#include "IStateRes.hpp"
#include "StringUtils.hpp"
#include "TimeDate.hpp"

class CgiResponseProcess: public IStateRes
{
	private:
		std::map<std::string, std::string>	_getHeaderMap(std::string &src);
		std::string							_getKey(std::string &line);
		std::string							_getValue(std::string &line);
		std::string							_getStatusLine(std::map<std::string, std::string> &src);
		bool								_existContent(std::map<std::string, std::string> &header);
		std::string							_getCgiBody(std::string &src);
		std::string							_getResponseHeaderLine(std::string key, std::string value);
		std::pair<std::string, std::string>	_makePair(std::string &line);
		void								_completeHeaderSet(std::map<std::string, std::string> &header);

	public:
		CgiResponseProcess(void);
		~CgiResponseProcess(void);

		StateResType handle(Event *event, ServerConfig configsData);
};
