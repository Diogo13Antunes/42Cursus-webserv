#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstring>

#define UPPER_CASE_LETTERS	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWER_CASE_LETTERS	"abcdefghijklmnopqrstuvwxyz"
#define DIGITS				"0123456789"
#define SPECIAL_CHARS		"*._-/\""

#define VALID_KEY_LETTERS	UPPER_CASE_LETTERS LOWER_CASE_LETTERS DIGITS SPECIAL_CHARS
#define WHITE_SPACE			"\n\t\r "

#define ERROR_FAIL_TO_OPEN_FILE				"Impossible to open or read from file: "
#define ERROR_INVALID_TABS					"Invalid tab"
#define ERROR_INVALID_IDENTATION_COUNT		"Invalid identation count"
#define ERROR_INVALID_NBR_QUOTES			"Invalid number of quotes"
#define ERROR_MISSING_SINGLE_COLON			"Missing single colon"
#define ERROR_INVALID_KEY					"Invalid key"
#define ERROR_INVALID_VALUE					"Invalid value"
#define ERROR_INVALID_CONFIG_OPTION			"Invalid config option: "

class Configs
{
	private:
		std::vector<std::string>		_validOptions;
		std::vector<std::string>		_fileContentVector; // Será removido
		std::map<size_t, std::string>	_fileContentMap;

		std::string						_errorMessage;

		void	_initValidOptions(void);

		bool	_getConfigFile(const char *configFile);
		bool	_isValidConfigFile(void);
		bool	_isValidConfigOptions(void);
		bool	_isValidKey(std::string &line);
		bool	_isValidValue(std::string &line);
		bool	_isValidConfigIndentation(void);
		bool	_isValidIndentationCount(std::string &line);
		bool	_isOnlyServerWithoutIndentation(std::string &line);

		void	_setErrorMessage(size_t line, std::string msg, std::string lineContent);
		void	_setErrorMessage(size_t line, std::string msg, std::string msg2, std::string lineContent);
		void	_setErrorMessage(std::string msg);
		void	_setErrorMessage(std::string msg, std::string msg2);

	public:
		Configs(void);
		Configs(const char *configsFileName);

		std::string	getErrorMessage(void);

		~Configs(void);

		std::vector<std::string>	&getFileContentVector(void);

		class InvalidConfigFileException: public std::exception
		{
			private:
				std::string _msg;
				char		*_fullMsg;

			public:
				InvalidConfigFileException(std::string msg);
				virtual ~InvalidConfigFileException() throw();

				const char *what() const throw();
		};

};
