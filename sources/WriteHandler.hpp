#pragma once

#include "IEventHandler.hpp"

class WriteHandler: public IEventHandler
{
	public:
		WriteHandler &operator=(const WriteHandler &src);
		WriteHandler(const WriteHandler &src);
		WriteHandler(void);
		~WriteHandler(void);
};
