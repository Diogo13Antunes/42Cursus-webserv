#pragma once

#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_LEN	1024
#define WHITE_SPACE	"\n\t\r "

class CGIExecuter
{
	private:
		std::string			_scriptInterpreter;
		std::string			_scriptName;
		std::string			_scriptInput;
		int					_pipe1[2];
		int					_pipe2[2];
		int					_pid;

		bool				_initPipes(void);
		std::string			_getScriptInterpreter(void);

		void				_closeAllFds(void);
		void				_closeFd(int *fd);

	public:
		CGIExecuter(void);
		~CGIExecuter(void);
	
		int			getReadFD(void);
		std::string	getResult(void);

		void		execute(std::string script, std::string message, char **env);
		bool		isEnded(void);

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
