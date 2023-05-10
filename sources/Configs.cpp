#include "Configs.hpp"

static bool			initConfigs(char *configFile);
static std::string	getString(std::string source, size_t *index);
static bool			isHashtagInsideQuotes(std::string src, size_t index);
static std::string	stringTrim(const std::string &str);

Configs::Configs(void)
{
	//Default Configs Constructor
}

Configs::Configs(const char *configsFileName)
{
	if (!_getConfigFile(configsFileName))
		throw InvalidConfigFileException();
}

Configs::Configs(const Configs &src)
{
	//Configs Copy Constructor
	*this = src;
}

Configs::~Configs(void)
{
	//Default Configs Destructor
}

Configs &Configs::operator=(const Configs &src)
{
	//Configs Copy Assignment Operator
	*this = src;
	return (*this);
}

static void	printConfigFile(std::vector<std::string> *file)
{
	for (int i = 0; i < (*file).size(); i++)
		Terminal::printMessages((*file).at(i).c_str());
}

void	Configs::_removeCommentsAndEmptyLines(void)
{
	for (size_t i = 0; i < _configFileVec.size(); i++)
	{
		for (size_t j = 0; j < _configFileVec.at(i).size(); j++)
		{
			if (_configFileVec.at(i)[j] == '#')
				if (!isHashtagInsideQuotes(_configFileVec.at(i), j))
					_configFileVec.at(i) = _configFileVec.at(i).substr(0, j);
		}
		if (_configFileVec.at(i).find_first_not_of("\n\r\t ") == _configFileVec.at(i).npos)
		{
			_configFileVec.erase(_configFileVec.begin() + i);
			i--;
		}
	}
}

void	Configs::_removeExtraWhiteSpaces(void)
{
	for (size_t i = 0; i < _configFileVec.size(); i++)
		_configFileVec.at(i) = stringTrim(_configFileVec.at(i));
}

// Checks if the file can be correctly open or not
// After open the file obtain the content of him
// Returns false if something went wrong or true if everything is OK
bool	Configs::_getConfigFile(const char *configFile)
{
	std::ifstream	file(configFile);
	std::string		buff;

	if (file.is_open())
	{
		while (std::getline(file, buff))
			_configFileVec.push_back(buff);
		file.close();
		printConfigFile(&_configFileVec);
		_removeCommentsAndEmptyLines();
		_removeExtraWhiteSpaces();
		Terminal::printMessages("-------------------------------------------");
		printConfigFile(&_configFileVec);
	}
	else
		return (false);
	return (true);
}

// Return true if the configs were done well, if not return false
bool	Configs::initConfigs(char *configFile)
{
	std::ifstream	file(configFile);
	std::string		buff;

	size_t		index = 0;
	char		res;
	//std::string word;

	while (1)
	{
		res = getNextToken(&index);
		if (!res)
			break;
		if (res == TOKEN_QUOTATION_MARKS)
		{
			//word = getString(this->_configFile, &index);
			//Terminal::printMessages(word.c_str());
		}
		if (_isToken(res) || res == ' ')
			index += 1;
	}
	return (true);
}

/**
 * Checks if a charecter is or not a Token
 * 
 * @return
 * True or False
*/
bool	Configs::_isToken(char c)
{
	if (c == TOKEN_CURLY_OPEN || c == TOKEN_CURLY_CLOSE
		|| c == TOKEN_ARRAY_OPEN || c == TOKEN_ARRAY_CLOSE
		|| c == TOKEN_COMMA || c == TOKEN_COLON
		|| c == TOKEN_QUOTATION_MARKS)
		return (true);
	return (false);
}

/**
 * Function to get the next token in the file
 * 
 * @param index starting point from where to find the next token
*/
char	Configs::getNextToken(size_t *index)
{
	size_t	i = 0;
	char	temp = 0;

	i = *index;
	while (1)
	{
		temp = 'a';//_configFile[i];
		if (temp == '\0' || _isToken(temp))
			break;
		i++;
	}
	*index = i;
	return (temp);
}

/**
 * Function to get a string inside quotes
 * 
 * @param source string to extract the result
 * @param index point to start getting the string
 * 
*/
static std::string	getString(std::string source, size_t *index)
{
	std::string	result;
	char		temp = 0;
	size_t		i;

	i = *index + 1;
	while (1)
	{
		temp = source[i];
		if (temp == TOKEN_QUOTATION_MARKS)
			break;
		result += temp;
		i++;
	}
	*index = i;
	return (result);
}

/* Exceptions */

const char *Configs::InvalidConfigFileException::what(void) const throw()
{
	return ("Invalid Configuration File");
}

/* Utils Functions */

static std::string	stringTrim(const std::string &str)
{
	std::string	trimmed = str;
	size_t		start = trimmed.find_first_not_of(" \t\r\n");
	size_t		end = trimmed.find_last_not_of(" \t\r\n");

	if (start != std::string::npos)
		trimmed = trimmed.substr(start);

	if (end != std::string::npos)
		trimmed = trimmed.substr(0, end + 1);

	return (trimmed);
}

static bool	isHashtagInsideQuotes(std::string src, size_t index)
{
	if (src[index] != '#')
		return (false);
	if (src.find_first_of('\"', index) == src.npos)
		return (false);
	if (src.find_last_of('\"', index) == src.npos)
		return (false);
	return (true);
}
