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
	std::string	data = "STDIN: here has to be sent the body (payload) and has to pass by epoll";

	ex = event->getCgiEx();
	env = _getEnvVariables(event, data);
	ex->execute("cgi-bin/cgi_script.py", data, env);
	_freeEnv(env);
	return (GETTING_DATA_CGI);
}

char	**ExecCgiState::_getEnvVariables(Event *event, std::string data)
{
	std::vector<std::string>	temp;

	temp.push_back("REQUEST_METHOD=" + event->getReqLineMethod());
	temp.push_back("SERVER_PROTOCOL=" + event->getReqLineHttpVersion());
	temp.push_back("CONTENT_LENGTH=" + _sizeToString(data.length()));
	temp.push_back("CONTENT_TYPE=" + event->getReqContentType());
	temp.push_back("QUERY_STRING=" + event->getQueryString());

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

std::string	ExecCgiState::_sizeToString(size_t number)
{
	std::stringstream ss;
	ss << number;

	return (ss.str());
}
