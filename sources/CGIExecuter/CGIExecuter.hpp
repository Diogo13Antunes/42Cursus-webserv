#pragma once

#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

class CGIExecuter
{
	private:
		const std::string	_scriptExecutor;
		std::string			_scriptName;
		std::string			_scriptInput;
		int					_pipe1[2];
		int					_pipe2[2];
		int					_pid;

		bool				_initPipes(void);

	public:
		CGIExecuter(void);
		~CGIExecuter(void);
	
		int			getReadFD(void);
		std::string	getResult(void);

		void		execute(std::string script, std::string message);
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
