#pragma once

#include "IEventHandler.hpp"
#include "HandleCgi.hpp"

class CGIHandler: public IEventHandler
{
	private:
		HandleCgi	*_handleCgi;

	public:
		CGIHandler(void);
		CGIHandler(HandleCgi *_handleCgi);
		~CGIHandler(void);

		void handleEvent(Event *event);
		EventType getHandleType(void);
};
