/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiExec.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:56:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/07 17:18:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiExec.hpp"
#include "ServerConfig.hpp"
#include "StringUtils.hpp"
#include "configs.hpp"

int CgiExec::execute(Event *event)
{
	int		p1[2];
	int		p2[2];
	int		pid;
	char	**env;

	if (pipe(p1) == -1 || pipe(p2) == -1)
		return (-1);
	env = _getEnvVars(event);
	if (!env)
	{
		_closePipe(p1);
		_closePipe(p2);
		return (-1);
	}
	pid = _execute(env, event->getResourcePath(), p1, p2);
	if (pid == -1)
	{
		_freeEnvVariables(env);
		return (-1);
	}
	_freeEnvVariables(env);
	event->setCgiWriteFd(p1[1]);
	//std::cout << "-------Write Fd cgi: " << p1[1] << std::endl;
	close(p1[0]);
	event->setCgiReadFd(p2[0]);
	//std::cout << "-------Read Fd cgi: " << p2[0] << std::endl;
	close(p2[1]);
	event->setCgiPid(pid);
	return (0);
}

bool CgiExec::isEnded(Event *event)
{
	int	cgiPid;
	int res;
	int	status;

	cgiPid = event->getCgiPid();
	res = waitpid(cgiPid, &status, WNOHANG);
	if (res < 0)
	{
		event->setCgiExitStatus(res);
		return (true);
	}
	else if (res == cgiPid)
	{
		status = WEXITSTATUS(status);
		event->setCgiExitStatus(status);
		return (true);
	}
	return (false);
}

char** CgiExec::_getEnvVars(Event *event)
{
	std::vector<std::string>	temp;
	ServerConfig				*serverConfigs;
	char 						**env;

	serverConfigs = event->getServerConfing();
	if (!serverConfigs)
		return (NULL);
	temp.push_back("SERVER_PROTOCOL=" + std::string(HTTP_VERSION));
	temp.push_back("REQUEST_METHOD=" + event->getReqLineMethod());
	temp.push_back("CONTENT_LENGTH=" + StringUtils::toString(event->getReqBodySize()));
	temp.push_back("CONTENT_TYPE=" + event->getReqContentType());
	temp.push_back("QUERY_STRING=" + event->getQueryString());
	temp.push_back("DOCUMENT_ROOT=" + serverConfigs->getUploadStore(event->getReqLinePath()));
	temp.push_back("REMOTE_ADDR=" + event->getIp());
	temp.push_back("SERVER_NAME=" + event->getReqHost());
	temp.push_back("SERVER_PORT=" + event->getPort());
	temp.push_back("SERVER_SOFTWARE=" + std::string(SERVER_SOFTWARE));

	env = new char*[temp.size() + 1];
	for (size_t i = 0; i < temp.size(); ++i) {
		env[i] = new char[temp[i].size() + 1];
		std::strcpy(env[i], temp[i].c_str());
	}
	env[temp.size()] = NULL;
	return (env);
}

void CgiExec::_closePipe(int *p)
{
	close(p[0]);
	close(p[1]);
}

std::string	CgiExec::_getScriptInterpreter(std::string scriptPath)
{
	std::ifstream	file(scriptPath.c_str());
	std::string		result;
	std::string		line;

	if (file.is_open())
	{
		std::getline(file, line);
		line = StringUtils::stringTrim(line);
		result = line.substr(line.find_first_not_of("#!"));
	}
	return (result);
}

void CgiExec::_freeEnvVariables(char **env)
{
	if (env)
	{
		for (size_t i = 0; env[i] ; i++)
			delete[] env[i];
		delete[] env;
	}
}

int CgiExec::_execute(char **env, std::string scriptPath, int *p1, int *p2)
{
	std::string scriptRunner;
	int pid;

	// pode ser um executável nesse caso tentar executar na mesma
	scriptRunner = _getScriptInterpreter(scriptPath);
	if (scriptRunner.empty())
		return (-1);
	const char *av[] = {scriptRunner.c_str(), scriptPath.c_str(), NULL};
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		dup2(p1[0], STDIN_FILENO);
		dup2(p2[1], STDOUT_FILENO);
		_closePipe(p1);
		_closePipe(p2);
		execve(scriptRunner.c_str(), const_cast<char**>(av), env);
		_freeEnvVariables(env);
		exit(-1);
	}
	return (pid);
}
