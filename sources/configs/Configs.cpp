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

bool	Configs::getNextConfig(std::string &key, std::string &value)
{
	static int	i = 0;
	size_t		index;
	std::string	temp;

	if (i == _configFileVec.size())
		return (false);
	temp = _configFileVec.at(i);
	index = temp.find_first_of(":");
	key = ConfigsUtils::stringTrim(temp.substr(0, index));
	value = ConfigsUtils::stringTrim(temp.substr(index + 1, temp.size() - 1));
	i++;
	return (true);
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
		{
			buff = ConfigsUtils::removeComments(buff);
			if (!buff.empty())
				_configFileVec.push_back(buff);
		}
		file.close();
	}
	else
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
		if (!ConfigsUtils::isSingleColon(_configFileVec.at(i)))
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
