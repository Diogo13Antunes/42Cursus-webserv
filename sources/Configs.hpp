#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "Terminal.hpp"
#include "Server.hpp"

#define	TOKEN_CURLY_OPEN		'{'
#define TOKEN_CURLY_CLOSE		'}'
#define TOKEN_ARRAY_OPEN		'['
#define TOKEN_ARRAY_CLOSE		']'
#define TOKEN_COMMA				','
#define TOKEN_COLON				':'
#define TOKEN_QUOTATION_MARKS	'\"'

class Configs
{
	private:

		std::vector<std::string>		_configFileVec;

		void							_removeCommentsAndEmptyLines(void);
		void							_removeExtraWhiteSpaces(void);
		
		bool							_getConfigFile(const char *configFile);
		bool							_isValidConfigFile(void);

		Configs &operator=(const Configs &src);
		Configs(const Configs &src);

	public:

		Configs(const char *configFileName);
		Configs(void);
		~Configs(void);

		class InvalidConfigFileException: public std::exception
		{
			public:
				const char *what() const throw();
		};

};
