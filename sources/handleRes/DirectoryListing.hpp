#pragma once

#include "IStateRes.hpp"

class DirectoryListing: public IStateRes
{
	private:
		//void		_getDirContent(std::string directory);
		std::map<std::string, std::string> _getDirContent(std::string directory);
		std::string	_getLastModificationDate(std::string path);
		

	public:
		DirectoryListing(void);
		~DirectoryListing(void);

		StateResType handle(Event *event, ServerConfig config);
};
