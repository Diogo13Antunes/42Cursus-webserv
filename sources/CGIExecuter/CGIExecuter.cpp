#include "CGIExecuter.hpp"

#include <signal.h>
#include <cstdlib>
#include <fcntl.h>

#define	NO_EXIT_STATUS	256
#define GENERIC_ERROR	1

/*CGIExecuter::CGIExecuter(void)
{
	if (!_initPipes())
		throw FailToIinitPipesException();
}*/

CGIExecuter::CGIExecuter(void): _statusCode(0)
{
	if (!_initPipes())
		throw FailToIinitPipesException();
	_execute(NULL, "cgi-bin/script.py");
}

// O construtor precisa de receber como parametro o que necessita de entrar dentro do _execute()
CGIExecuter::CGIExecuter(ServerConfig *config, RequestParser &request, std::string scriptName): _statusCode(0)
{
	_serverConfigs = config;
	_request = request;
	if (!_initPipes())
		throw FailToIinitPipesException();
	_env = _getEnvVariables();
	_execute(_env, scriptName);
}

/*
CGIExecuter::~CGIExecuter(void)
{
	if (!this->isEnded())
	{
		std::cout << "Tenta fazer o kill" << std::endl;
		if (kill(_pid, SIGTERM) == -1)
			std::cout << "Webserv: Error terminating SGI script" << std::endl;

	}
	_closeAllFds();
}
*/

CGIExecuter::~CGIExecuter(void)
{
	if (this->isEnded() == NO_EXIT_STATUS)
	{
		std::cout << "Tenta fazer o kill" << std::endl;
		if (kill(_pid, SIGTERM) == -1)
			std::cout << "Webserv: Error terminating SGI script" << std::endl;
	}
	// _closeAllFds();
	_closeFd(&_pipe2[0]);
}

void	CGIExecuter::execute(std::string script, std::string message, char **env)
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
		dup2(_pipe1[0], STDIN_FILENO);
		dup2(_pipe2[1], STDOUT_FILENO);
		_closeAllFds();
		execve(_scriptInterpreter.c_str(), const_cast<char**>(av), env);
		//throw ExecutionErrorException();
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
bool CGIExecuter::isEnded(void)
{
	int res;

	res = waitpid(_pid, NULL, WNOHANG);
	if (res == _pid || res < 0)
		return (true);
	return (false);
}
*/

int CGIExecuter::isEnded(void)
{
	int res;
	int	status;

	status = NO_EXIT_STATUS;
	res = waitpid(_pid, &status, WNOHANG);
	if (res == _pid)
		status = WEXITSTATUS(status);
	else if (res < 0)
		status = res;
	return (status);
}

int	CGIExecuter::getReadFD(void)
{
	return (_pipe2[0]);
}

int	CGIExecuter::getWriteFD(void)
{
	return (_pipe1[1]);
}

int CGIExecuter::writeToScript(const char *str)
{
	int fd;
	fd = this->getWriteFD();
	return (write(fd, str, std::strlen(str)));
}

int CGIExecuter::readFromScript(std::string &str)
{
	char	buffer[500000];
	int		fd;
	int		nRead;

	fd = this->getReadFD();
	nRead = read(fd, buffer, 500000);
	str.assign(buffer, nRead);
	return (nRead);
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

//depercated acho que já existe outra string trim nos utils
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

void CGIExecuter::_execute(char **env, std::string path)
{
	_scriptName = path;
	_scriptInterpreter = _getScriptInterpreter();

	if (_scriptInterpreter.empty())
		throw ExecutionErrorException();

	const char *av[] = {_scriptInterpreter.c_str(), _scriptName.c_str(), NULL};

	_pid = fork();
	if (_pid == -1)
		throw FailToCreateChildProcessException();

	if (_pid == 0)
	{
		dup2(_pipe1[0], STDIN_FILENO);
		dup2(_pipe2[1], STDOUT_FILENO);
		_closeAllFds();
		execve(_scriptInterpreter.c_str(), const_cast<char**>(av), env);
		throw ExecutionErrorException();
		return ;
	}
}

std::string sizeToString(size_t number)
{
	std::stringstream ss;
	ss << number;

	return (ss.str());
}

char	**CGIExecuter::_getEnvVariables(void)
{
	std::vector<std::string>	temp;

	temp.push_back("SERVER_PROTOCOL=HTTP/1.1");
	temp.push_back("REQUEST_METHOD=" + _request.getReqLineMethod());
	temp.push_back("CONTENT_LENGTH=" + sizeToString(_request.getRequestBody().size()));
	temp.push_back("CONTENT_TYPE=" + _request.getHeaderField("content-type").at(0));
	temp.push_back("QUERY_STRING=" + _request.getQueryString());
	temp.push_back("DOCUMENT_ROOT=" + _serverConfigs->getUploadStore(_request.getReqLinePath()));

	char **env = new char*[temp.size() + 1];

	env[temp.size()] = NULL;

	for (size_t i = 0; i < temp.size(); ++i) {
		env[i] = new char[temp[i].size() + 1];
		std::strcpy(env[i], temp[i].c_str());
	}

	return (env);
}
