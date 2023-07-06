#pragma once

#include "IEventHandler.hpp"

class CGIHandler: public IEventHandler
{
	public:
		CGIHandler(void);
		~CGIHandler(void);
			
		void handleEvent(Event *event);
		EventType getHandleType(void);
};
