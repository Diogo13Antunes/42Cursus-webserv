#pragma once

#include "IStateCGI.hpp"

class ExecCgiState: public IStateCGI
{
	public:
		ExecCgiState(void);
		~ExecCgiState(void);

		StateCgiType handle(Event *event);
};
