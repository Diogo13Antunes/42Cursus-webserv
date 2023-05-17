#pragma once

#include "IEventHandler.hpp"
#include <map>

class EventLoop
{
	std::map<int, IEventHandler> handlers;

	public:
		EventLoop(void);
		EventLoop(const EventLoop &src);
		~EventLoop(void);
		EventLoop &operator=(const EventLoop &src);

		void registerEvent(IEventHandler *event);
		void unregisterEvent(IEventHandler *event);
};
