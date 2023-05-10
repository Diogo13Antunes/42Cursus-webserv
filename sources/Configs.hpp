#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "Terminal.hpp"
#include "Server.hpp"

#define VALID_KEY_LETTERS	"abcdefghijklmnopqrstuvwxyz_-"
#define WHITE_SPACE			"\n\t\r "

class Configs
{
	private:

		std::vector<std::string>		_configFileVec;

		void							_removeCommentsAndEmptyLines(void);
		void							_removeExtraWhiteSpaces(void);

		bool							_getConfigFile(const char *configFile);

		bool							_isValidConfigFile(void);
		bool							_isWithSingleColon(std::string &line);
		bool							_isValidKey(std::string	&line);
		bool							_isValidData(std::string &line);

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
