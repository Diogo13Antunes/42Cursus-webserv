#pragma once

#include "IStateCGI.hpp"

class ExecCgiState: public IStateCGI
{
	private:
		char**		_getEnvVariables(Event *event, std::string data);
		void		_freeEnv(char **env);
		std::string	_sizeToString(size_t number);

	public:
		ExecCgiState(void);
		~ExecCgiState(void);

		StateCgiType handle(Event *event);
};
