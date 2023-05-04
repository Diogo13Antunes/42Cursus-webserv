#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Terminal.hpp"

#define	TOKEN_CURLY_OPEN		'{'
#define TOKEN_CURLY_CLOSE		'}'
#define TOKEN_ARRAY_OPEN		'['
#define TOKEN_ARRAY_CLOSE		']'
#define TOKEN_COMMA				','
#define TOKEN_COLON				':'
#define TOKEN_QUOTATION_MARKS	'\"'

class Configs
{
	public:

		class Server
		{
			public:

				void		setPort(int	newPort);
				void		setServerName(std::string newServerName);
				void		setRoot(std::string newRoot);
				void		setIndex(std::string newIndex);

				int			getPort();
				std::string	getServerName();
				std::string	getRoot();
				std::string	getIndex();

			private:
			
				int			_port;
				std::string	_serverName;
				std::string	_root;
				std::string	_index;
		};

		Configs(char *configsFileName);
		Configs(void);
		~Configs(void);

	private:

		char	getNextToken();

		Configs &operator=(const Configs &src);
		Configs(const Configs &src);

		std::string	_configFile;
};
