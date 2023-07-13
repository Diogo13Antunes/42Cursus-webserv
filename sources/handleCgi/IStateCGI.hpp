#pragma once

#include "Event.hpp"
#include "StateCgiType.hpp"

class IStateCGI
{
	public:
		virtual ~IStateCGI(void) {};
		virtual StateCgiType handle(Event *event) = 0;
};
