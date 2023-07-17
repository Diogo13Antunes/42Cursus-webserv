#pragma once

#include "IStateCGI.hpp"

class ExecCgiState: public IStateCGI
{
	private:
		char	**_getEnvVariables(Event *event);
		void	_freeEnv(char **env);

	public:
		ExecCgiState(void);
		~ExecCgiState(void);

		StateCgiType handle(Event *event);
};
