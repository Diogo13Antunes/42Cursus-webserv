#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "Terminal.hpp"
#include "ConfigsUtils.hpp"

class Configs
{
	private:

		std::vector<std::string>		_configFileVec;

		void							_removeCommentsAndEmptyLines(void);
		void							_removeExtraWhiteSpaces(void);
		bool							_getConfigFile(const char *configFile);
		bool							_isValidConfigFile(void);
		bool							_isSingleColon(std::string &line);
		bool							_isValidKey(std::string	&line);
		bool							_isValidValue(std::string &line);

	public:

		Configs(const char *configFileName);
		~Configs(void);

		class InvalidConfigFileException: public std::exception
		{
			public:
				const char *what() const throw();
		};

		bool	getNextConfig(std::string &key, std::string &value);

};
