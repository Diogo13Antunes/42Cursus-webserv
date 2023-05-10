#include "Configs.hpp"

static bool			initConfigs(char *configFile);
static std::string	getString(std::string source, size_t *index);
static bool			isInsideQuotes(std::string src, size_t index);
static std::string	stringTrim(const std::string &str);

Configs::Configs(void)
{
	//Default Configs Constructor
}

Configs::Configs(const char *configsFileName)
{
	if (!_getConfigFile(configsFileName))
		throw InvalidConfigFileException();
	if (!_isValidConfigFile())
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
				if (!isInsideQuotes(_configFileVec.at(i), j))
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

bool	Configs::_isValidConfigFile(void)
{
	return (true);
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

static bool	isInsideQuotes(std::string src, size_t index)
{
	if (src.find_first_of('\"', index) == src.npos)
		return (false);
	if (src.find_last_of('\"', index) == src.npos)
		return (false);
	return (true);
}
