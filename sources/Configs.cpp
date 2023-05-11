#include "Configs.hpp"

static bool			initConfigs(char *configFile);
static std::string	getString(std::string source, size_t *index);
static bool			isInsideQuotes(std::string src, size_t index);
static std::string	stringTrim(const std::string &str);
static bool			isValidArray(std::string &array);
static bool			isValisNbrQuotes(std::string &data);

Configs::Configs(const char *configsFileName)
{
	if (!_getConfigFile(configsFileName))
		throw InvalidConfigFileException();
	if (!_isValidConfigFile())
		throw InvalidConfigFileException();
	Terminal::printMessages("\n------------\nChecks: OK\n------------\n");
}

Configs::~Configs(void)
{
	//Default Configs Destructor
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

bool	Configs::_isSingleColon(std::string &line)
{
	int	count = 0;
	
	for (size_t i = 0; i < line.size(); i++)
		if (line[i] == ':' && !isInsideQuotes(line, i))
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
	key = stringTrim(key);
	if (key.find_first_not_of(VALID_KEY_LETTERS) != key.npos)
		return (false);
	return (true);
}

bool	Configs::_isValidValue(std::string &line)
{
	std::string	value;

	value = line.substr(line.find_first_of(":") + 1, line.size());
	value = stringTrim(value);
	if (value.find_first_of("[") != value.npos || value.find_first_of("]") != value.npos)
	{
		if (!isValidArray(value))
			return (false);
	}
	else if (value.find_first_of("\"") != value.npos)
	{
		if (!isValisNbrQuotes(value))
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

static bool	isValidArray(std::string &array)
{
	size_t						nbrBrackets = 0;
	size_t						nbrQuotes = 0;
	std::string					temp;
	size_t						a = 1;

	for (size_t i = 0; i < array.size(); i++)
	{
		if (array[i] == '[')
			nbrBrackets++;
		else if (array[i] == ']')
			nbrBrackets--;
		else if (array[i] == '\"')
			nbrQuotes++;
	}
	if (nbrBrackets != 0 || nbrQuotes % 2 != 0)
		return (false);
	while (array[a])
	{
		while (array[a] != ',' && array[a + 1])
			temp += array[a++];
		if (temp.find_first_not_of(WHITE_SPACE) == temp.npos)
			return (false);
		temp.clear();
		a++;
	}
	return (true);
}

static bool	isValisNbrQuotes(std::string &data)
{
	size_t nbrQuotes = 0;

	for (size_t i = 0; i < data.size(); i++)
		if (data[i] == '\"')
			nbrQuotes++;
	if (nbrQuotes != 2)
		return (false);
	return (true);
}
