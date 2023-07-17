#include "ExecCgiState.hpp"

#include "Terminal.hpp"

ExecCgiState::ExecCgiState(void)
{
	// Default ExecCgiState Constructor
}

ExecCgiState::~ExecCgiState(void)
{
	// Default ExecCgiState Destructor
}

#include <cstdlib>

/*
	Criar estado de erro para apanhar as excessoews do executer.
*/
StateCgiType ExecCgiState::handle(Event *event)
{
	CGIExecuter *ex;
	char		**env;

	ex = event->getCgiEx();
	
	env = _getEnvVariables(event);

	ex->execute("cgi-bin/cgi_script.py", "Hi From Python", env);

	_freeEnv(env);
	
	return (GETTING_DATA_CGI);
}

char	**ExecCgiState::_getEnvVariables(Event *event)
{
	std::vector<std::string>	temp;
	std::string					aux[2];

	aux[0] = "REQUEST_METHOD=" + event->getReqMethod();

	if (!event->getQueryString().empty())
		aux[1] = "QUERY_STRING=" + event->getQueryString();

	for (size_t i = 0; i < 2; i++)
		if (!aux[i].empty())
			temp.push_back(aux[i]);

	char **env = new char*[temp.size() + 1];

	env[temp.size()] = NULL;

	for (size_t i = 0; i < temp.size(); ++i) {
		env[i] = new char[temp[i].size() + 1];
		std::strcpy(env[i], temp[i].c_str());
	}

	return (env);
}

void	ExecCgiState::_freeEnv(char **env)
{
	if (env)
	{
		for (size_t i = 0; env[i] ; i++)
			delete[] env[i];
		delete[] env;
	}
}
