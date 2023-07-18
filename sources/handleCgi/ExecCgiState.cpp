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
	std::string	data = "Hi From Python";

	ex = event->getCgiEx();
	
	std::printf("Here 1\n");
	env = _getEnvVariables(event, data);
	std::printf("Here 2\n");

	ex->execute("cgi-bin/cgi_script.py", data, env);

	_freeEnv(env);
	
	return (GETTING_DATA_CGI);
}

char	**ExecCgiState::_getEnvVariables(Event *event, std::string data)
{
	std::vector<std::string>	temp;
	std::string					aux[5];

	std::printf("Here 1.1\n");
	
	aux[0] = "REQUEST_METHOD=" + event->getReqMethod();
	
	std::printf("Here 1.1.1\n");
	
	aux[1] = "SERVER_PROTOCOL=" + event->getServerProtocol();

	std::printf("Here 1.1.2\n");

	aux[2] = "CONTENT_LENGTH=" + _sizeToString(data.length());

	std::printf("Here 1.1.3\n");

	if (!event->getQueryString().empty())
	{

		std::printf("Here 1.1.4\n");
		if (!event->getReqContentType().empty())
		{
			aux[3] = "CONTENT_TYPE=" + event->getReqContentType();
			std::printf("Here 1.1.5\n");
		}
		aux[4] = "QUERY_STRING=" + event->getQueryString();
		std::printf("Here 1.1.6\n");
	}

	std::printf("Here 1.2\n");

	for (size_t i = 0; i < 5; i++)
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

std::string	ExecCgiState::_sizeToString(size_t number)
{
	std::stringstream ss;
	ss << number;

	return (ss.str());
}
