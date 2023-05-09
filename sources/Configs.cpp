#include "Configs.hpp"

static bool			initConfigs(char *configFile);
static std::string	getString(std::string source, size_t *index);
static bool isToken(char c);

Configs::Configs(void)
{
	//Default Configs Constructor
}

Configs::Configs(const char *configsFileName)
{
	if (!_getConfigFile(configsFileName) || !_isValidJsonFile())
		throw InvalidConfigFileException();
	Terminal::printMessages(this->_configFile.c_str());
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

bool	Configs::_getConfigFile(const char *configFile)
{
	std::ifstream	file(configFile);
	std::string		buff;

	if (file.is_open())
	{
		while (std::getline(file, buff))
				_configFile += buff;
		file.close();
	}
	else
		return (false);
	return (true);
}

bool	Configs::_isValidJsonFile(void)
{
	int	counterBrackets = 0;
	int	counterQuotes = 0;

	if (_configFile.empty())
		return (false);
	for (int i = 0; _configFile[i]; i++)
	{
		if (_configFile[i] == '{' || _configFile[i] == '['
			|| _configFile[i] == '}' || _configFile[i] == ']')
			counterBrackets++;
		else if (_configFile[i] == '\"')
			counterQuotes++;
	}
	if (counterQuotes % 2 != 0 || counterBrackets % 2 != 0)
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
	std::string word;

	while (1)
	{
		res = getNextToken(&index);
		if (!res)
			break;
		if (res == TOKEN_QUOTATION_MARKS)
		{
			word = getString(this->_configFile, &index);
			Terminal::printMessages(word.c_str());
		}
		if (isToken(res) || res == ' ')
			index += 1;
	}
	return (true);
}

static bool isToken(char c)
{
	if (c == TOKEN_CURLY_OPEN || c == TOKEN_CURLY_CLOSE
		|| c == TOKEN_ARRAY_OPEN || c == TOKEN_ARRAY_CLOSE
		|| c == TOKEN_COMMA || c == TOKEN_COLON
		|| c == TOKEN_QUOTATION_MARKS)
		return (true);
	return (false);
}

char	Configs::getNextToken(size_t *index)
{
	size_t			i = 0;
	char			temp = 0;

	i = *index;
	while (1)
	{
		temp = this->_configFile[i];
		if (temp == '\0' || isToken(temp))
			break;
		i++;
	}
	*index = i;
	return (temp);
}

// Function to get a string inside quotes 
// source -> source string to extract the result
// index -> index to start getting the string
// Example -> "example" = example
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
