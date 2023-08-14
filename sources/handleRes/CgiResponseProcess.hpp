#pragma once

#include <string>
#include <iostream>
#include "IStateRes.hpp"
#include "StringUtils.hpp"

class CgiResponseProcess: public IStateRes
{
	private:
		std::vector<std::string>	_getHeaderVector(std::string &src);
		std::string					_getKey(std::string &line);
		std::string					_getValue(std::string &line);
		std::string					_invalidCgiResponse(void);
		std::string					_getStatusLine(std::vector<std::string> &src);
		bool						_existContent(std::vector<std::string> &header);
		std::string					_getCgiBody(std::string &src);

	public:
		CgiResponseProcess(void);
		~CgiResponseProcess(void);

		StateResType handle(Event *event, ConfigsData configsData);
};
