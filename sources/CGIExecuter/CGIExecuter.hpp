#pragma once

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define WHITE_SPACE	"\n\t\r "

#include "ServerConfig.hpp"
#include "RequestParser.hpp"
#include "StringUtils.hpp"
#include "configs.hpp"

class CGIExecuter
{
	private:

		ServerConfig		*_serverConfigs;
		RequestParser		_request;

		std::string			_scriptInterpreter;
		std::string			_scriptName;
		std::string			_scriptInput;
		int					_pipe1[2];
		int					_pipe2[2];
		int					_pid;
		int					_statusCode;
		char				**_env;

		bool				_initPipes(void);
		std::string			_getScriptInterpreter(void);
		void				_closeAllFds(void);
		void				_closeFd(int *fd);
		void				_execute(char **env, std::string path);
		char 				**_getEnvVariables(void);
		void				_freeEnvVariables(void);

	public:
		CGIExecuter(void);
		CGIExecuter(ServerConfig *config, RequestParser &request, std::string scriptName);
		~CGIExecuter(void);

		int			getReadFD(void);
		int			getWriteFD(void);
		int			writeToScript(const char *str);
		int			readFromScript(std::string &str);
		int			isEnded(void);

		class ExecutionErrorException: public std::exception
		{
			public:
				const char *what() const throw();
		};

		class FailToIinitPipesException: public std::exception
		{
			public:
				const char *what() const throw();
		};

		class FailToCreateChildProcessException: public std::exception
		{
			public:
				const char *what() const throw();
		};

	/*
		killProcess - timeout - signal kill
	*/

};
