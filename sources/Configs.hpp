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

		class InvalidConfigFileException: public std::exception
		{
			public:
				const char *what() const throw();
		};

		Configs(const char *configFileName);
		Configs(void);
		~Configs(void);

	private:

		bool	_getConfigFile(const char *configFile);
		bool	_isValidJsonFile(void);

		bool	_isToken(char c);


		bool	initConfigs(char *configFile);

		char	getNextToken(size_t *index);

		Configs &operator=(const Configs &src);
		Configs(const Configs &src);

		std::string	_configFile;
};
