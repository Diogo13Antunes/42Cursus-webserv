#include "CGIExecuter.hpp"

#include <signal.h>

#include <cstdlib>

CGIExecuter::CGIExecuter(void)
{
	// Default CGIExecuter Constructor
	if (!_initPipes())
		throw FailToIinitPipesException();
}

CGIExecuter::~CGIExecuter(void)
{
	// Default CGIExecuter Destructor

	//std::cout << "Destrutor do CGIExecuter" << std::endl;

	if (!this->isEnded())
	{
		std::cout << "Tenta fazer o kill" << std::endl;
		if (kill(_pid, SIGTERM) == -1)
			std::cout << "Webserv: Error terminating SGI script" << std::endl;

	}
	_closeAllFds();
}

void	CGIExecuter::execute(std::string script, std::string message)
{
	_scriptName = script;
	_scriptInterpreter = _getScriptInterpreter();

	if (_scriptInterpreter.empty())
		throw ExecutionErrorException();

	const char *av[] = {_scriptInterpreter.c_str(), _scriptName.c_str(), NULL};

	_pid = fork();
	if (_pid == -1)
		throw FailToCreateChildProcessException();

	if (_pid == 0)
	{
		//_pid = getpid();

		//std::cout << "PID CHILD: " << _pid << std::endl;

		dup2(_pipe1[0], STDIN_FILENO);
		dup2(_pipe2[1], STDOUT_FILENO);
		//_closeFd(&_pipe1[1]);
		//_closeFd(&_pipe2[0]);
		_closeAllFds();

		/*
		std::string s;

		char **env;// = {"key=value", "key=teste"};

		env = (char**) malloc(sizeof(char *) * 3);

		env[0] = (char *) malloc(sizeof(char) * strlen("key=value") + 1);
		env[1] = (char *) malloc(sizeof(char) * strlen("key=value") + 1);
		env[2] = NULL;

		s = "key=value";

		strcpy(env[0], s.c_str());
		strcpy(env[1], s.c_str());

		//env[0] = "key=value\0";*/

		execve(_scriptInterpreter.c_str(), const_cast<char**>(av), NULL);
		throw ExecutionErrorException();
		return ;
	}
	else
	{
		write(_pipe1[1], message.c_str(), message.size());

		_closeFd(&_pipe1[0]);
		_closeFd(&_pipe1[1]);
		_closeFd(&_pipe2[1]);
	}
}
/*
bool	CGIExecuter::isEnded(void)
{
	int status;
	int res;

	res = waitpid(_pid, &status, WNOHANG);

	std::cout << "Status: " << status << std::endl;
	std::cout << "Result: " << res << std::endl;

	if (status == 0)
		return (true);

	//if (WIFEXITED(status))
	//	return (true);
	return (false);
}
*/

bool CGIExecuter::isEnded(void)
{
	//std::cout << "PID TESTE FECHAMENTO: " << _pid << std::endl;
	int res;

	res = waitpid(_pid, NULL, WNOHANG);

	//std::cout << "Retorno do waitpid: " << res << std::endl;
	if (res == _pid || res < 0)
	{
		//std::cout << "terminou: pid: "  << _pid << " res: " << res << std::endl;
		return (true);
	}
	return (false);
}


int	CGIExecuter::getReadFD(void)
{
	return (_pipe2[0]);
}

/* Exceptions */

const char *CGIExecuter::ExecutionErrorException::what(void) const throw()
{
	return ("ExecutionErrorException: Error when try to execute an CGI Script.");
}

const char *CGIExecuter::FailToIinitPipesException::what(void) const throw()
{
	return ("FailToIinitPipesException: Error when try to open pipes.");
}

const char *CGIExecuter::FailToCreateChildProcessException::what(void) const throw()
{
	return ("FailToCreateChildProcessException: Error when try to create a child process.");
}

/* Class Private Functions */

bool	CGIExecuter::_initPipes(void)
{
	if (pipe(_pipe1) == -1 || pipe(_pipe2) == -1)
		return (false);
	return (true);
}

static void stringTrim(std::string &str);

std::string	CGIExecuter::_getScriptInterpreter(void)
{
	std::ifstream	file(_scriptName.c_str());
	std::string		result;
	std::string		line;

	if (file.is_open())
	{
		std::getline(file, line);
		stringTrim(line);
		result = line.substr(line.find_first_not_of("#!"));
	}
	return (result);
}

void	CGIExecuter::_closeFd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	CGIExecuter::_closeAllFds(void)
{
	_closeFd(&_pipe1[0]);
	_closeFd(&_pipe1[1]);
	_closeFd(&_pipe2[0]);
	_closeFd(&_pipe2[1]);
}

static void stringTrim(std::string &str)
{
	std::string	trimmed;
	size_t		start;
	size_t		end;
	size_t		len;

	start = str.find_first_not_of(WHITE_SPACE);
	end = str.find_last_not_of(WHITE_SPACE);
	len = end - start + 1;
	trimmed = str.substr(start, len);
	str = trimmed;
}
