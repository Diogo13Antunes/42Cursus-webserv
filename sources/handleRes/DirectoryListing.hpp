#pragma once

#include "IStateRes.hpp"

class DirectoryListing: public IStateRes
{
	public:
		DirectoryListing(void);
		~DirectoryListing(void);

		StateResType handle(Event *event, ServerConfig config);
};
