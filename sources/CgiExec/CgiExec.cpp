/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiExec.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:56:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 13:12:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CgiExec.hpp"
#include "ServerConfig.hpp"
#include "StringUtils.hpp"
#include "configs.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

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
	close(p1[0]);
	event->setCgiReadFd(p2[0]);
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
	temp.push_back("DOCUMENT_ROOT=" + serverConfigs->getUploadStore(event->getRoute()));
	temp.push_back("REMOTE_ADDR=" + event->getIp());
	temp.push_back("SERVER_NAME=" + event->getReqHost());
	temp.push_back("SERVER_PORT=" + event->getPort());
	temp.push_back("SERVER_SOFTWARE=" + std::string(SERVER_SOFTWARE));
	temp.push_back("PATH_INFO=" + event->getReqLinePath());

	/*
	std::cout << "====================================" << std::endl;
	std::cout << "SERVER_PROTOCOL=" << std::string(HTTP_VERSION) << std::endl;
	std::cout << "REQUEST_METHOD="  << event->getReqLineMethod() << std::endl;
	std::cout << "CONTENT_LENGTH="  << StringUtils::toString(event->getReqBodySize()) << std::endl;
	std::cout << "CONTENT_TYPE="    << event->getReqContentType() << std::endl;
	std::cout << "QUERY_STRING="    << event->getQueryString() << std::endl;
	std::cout << "DOCUMENT_ROOT="   << serverConfigs->getUploadStore(event->getRoute()) << std::endl;
	std::cout << "REMOTE_ADDR="     << event->getIp() << std::endl;
	std::cout << "SERVER_NAME="     << event->getReqHost() << std::endl;
	std::cout << "SERVER_PORT="     << event->getPort() << std::endl;
	std::cout << "SERVER_SOFTWARE=" << std::string(SERVER_SOFTWARE) << std::endl;
	std::cout << "PATH_INFO="       << event->getReqLinePath() << std::endl;
	*/


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
	size_t			idx;

	if (!file.is_open())
		return (result);
	std::getline(file, line);
	if (line.empty())
		return (result);
	line = StringUtils::stringTrim(line);
	idx = line.find("#!");
	if (idx == 0)
		result = line.substr(2);
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

	scriptRunner = _getScriptInterpreter(scriptPath);
	if (scriptRunner.empty())
		scriptRunner.assign(scriptPath);
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
