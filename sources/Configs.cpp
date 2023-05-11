#include "Configs.hpp"

static bool			initConfigs(char *configFile);
static std::string	getString(std::string source, size_t *index);

Configs::Configs(const char *configsFileName)
{
	if (!_getConfigFile(configsFileName))
		throw InvalidConfigFileException();
	if (!_isValidConfigFile())
		throw InvalidConfigFileException();
}

Configs::~Configs(void)
{
	//Default Configs Destructor
}

void	Configs::_removeCommentsAndEmptyLines(void)
{
	for (size_t i = 0; i < _configFileVec.size(); i++)
	{
		for (size_t j = 0; j < _configFileVec.at(i).size(); j++)
		{
			if (_configFileVec.at(i)[j] == '#')
				if (!ConfigsUtils::isInsideQuotes(_configFileVec.at(i), j))
					_configFileVec.at(i) = _configFileVec.at(i).substr(0, j);
		}
		if (_configFileVec.at(i).find_first_not_of(WHITE_SPACE) == _configFileVec.at(i).npos)
		{
			_configFileVec.erase(_configFileVec.begin() + i);
			i--;
		}
	}
}

void	Configs::_removeExtraWhiteSpaces(void)
{
	for (size_t i = 0; i < _configFileVec.size(); i++)
		_configFileVec.at(i) = ConfigsUtils::stringTrim(_configFileVec.at(i));
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
		_removeCommentsAndEmptyLines();
		_removeExtraWhiteSpaces();
	}
	else
		return (false);
	return (true);
}

bool	Configs::_isSingleColon(std::string &line)
{
	int	count = 0;
	
	for (size_t i = 0; i < line.size(); i++)
		if (line[i] == ':' && !ConfigsUtils::isInsideQuotes(line, i))
			count++;
	if (count != 1)
		return (false);
	return (true);
}

bool	Configs::_isValidKey(std::string &line)
{
	std::string	key;
	size_t		i;

	key = line.substr(0, line.find_first_of(":"));
	key = ConfigsUtils::stringTrim(key);
	if (key.find_first_not_of(VALID_KEY_LETTERS) != key.npos)
		return (false);
	return (true);
}

bool	Configs::_isValidValue(std::string &line)
{
	std::string	value;

	value = line.substr(line.find_first_of(":") + 1, line.size());
	value = ConfigsUtils::stringTrim(value);
	if (value.find_first_of("[") != value.npos || value.find_first_of("]") != value.npos)
	{
		if (!ConfigsUtils::isValidArray(value))
			return (false);
	}
	else if (value.find_first_of("\"") != value.npos)
	{
		if (!ConfigsUtils::isValisNbrQuotes(value))
			return (false);
		if (value[0] != '\"' || value[value.size() - 1] != '\"')
			return (false);
	}
	return (true);
}

bool	Configs::_isValidConfigFile(void)
{
	for (size_t i = 0; i < _configFileVec.size(); i++)
	{
		if (!_isSingleColon(_configFileVec.at(i)))
			return (false);
		else if (!_isValidKey(_configFileVec.at(i)))
			return (false);
		else if (!_isValidValue(_configFileVec.at(i)))
			return (false);
	}
	return (true);
}

/* Exceptions */

const char *Configs::InvalidConfigFileException::what(void) const throw()
{
	return ("InvalidConfigFileException: Invalid Config File");
}
