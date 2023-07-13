#pragma once

#include "IStateCGI.hpp"
#include "StateCgiType.hpp"

#define SIZE_BUFFER	100000

class GettingDataCgiState: public IStateCGI
{
	public:
		GettingDataCgiState(void);
		~GettingDataCgiState(void);

		StateCgiType handle(Event *event);
};
