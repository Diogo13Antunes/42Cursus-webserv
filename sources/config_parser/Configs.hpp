#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#define UPPER_CASE_LETTERS	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWER_CASE_LETTERS	"abcdefghijklmnopqrstuvwxyz"
#define DIGITS				"0123456789"
#define SPECIAL_CHARS		"_-/\""

#define VALID_KEY_LETTERS	UPPER_CASE_LETTERS LOWER_CASE_LETTERS DIGITS SPECIAL_CHARS
#define WHITE_SPACE			"\n\t\r "

class Configs
{
	private:
		std::vector<std::string>	_validOptions;
		std::vector<std::string>	_fileContentVector;

		void	_initValidOptions(void);

		bool	_getConfigFile(const char *configFile);
		bool	_isValidConfigFile(void);
		bool	_isValidConfigOptions(void);
		bool	_isValidKey(std::string &line);
		bool	_isValidValue(std::string &line);
		bool	_isValidConfigIndentation(void);
		bool	_isValidIndentationCount(std::string &line);
		bool	_isOnlyServerWithoutIndentation(std::string &line);

	public:
		Configs(void);
		Configs(const char *configsFileName);
		~Configs(void);

		std::vector<std::string>	&getFileContentVector(void);

		class InvalidConfigFileException: public std::exception
		{
			public:
				const char *what() const throw();
		};

};
