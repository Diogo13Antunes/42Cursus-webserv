#include "Configs.hpp"

static bool			initConfigs(char *configFile);
static std::string	getString(std::string source, size_t *index);
static bool isToken(char c);

Configs::Configs(void)
{
	//Default Configs Constructor
}

Configs::Configs(char *configsFileName)
{
	initConfigs(configsFileName);
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

// Return true if the configs were done well, if not return false
bool	Configs::initConfigs(char *configFile)
{
	std::ifstream	file(configFile);
	std::string		buff;

	size_t	index = 0;

	if (file.is_open())
	{
		Terminal::printMessages("File opened successfully");
		while (std::getline(file, buff))
				this->_configFile += buff;
		Terminal::printMessages("File ->");
		Terminal::printMessages(this->_configFile.c_str());

		char		res;
		std::string word;

		while (1)
		{
			res = getNextToken(&index);
			if (!res)
				break;
			if (res == TOKEN_QUOTATION_MARKS)
			{
				word += "Word ";
				word += getString(this->_configFile, &index);
				Terminal::printMessages(word.c_str());
			}
			if (isToken(res) || res == ' ')
				index += 1;
			word.clear();
		}
	}
	else
	{
		Terminal::printErrors("Impossible to read from Configuration File");
		return (false);
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

/* Config Server inner class methods */

void	Configs::Server::setPort(int	newPort)
{
	this->_port = newPort;
}

void	Configs::Server::setServerName(std::string newServerName)
{
	this->_serverName = newServerName;
}

void	Configs::Server::setRoot(std::string newRoot)
{
	this->_root = newRoot;
}

void	Configs::Server::setIndex(std::string newIndex)
{
	this->_index = newIndex;
}

int	Configs::Server::getPort()
{
	return (this->_port);
}

std::string	Configs::Server::getServerName()
{
	return (this->_serverName);
}

std::string	Configs::Server::getRoot()
{
	return (this->_root);
}

std::string	Configs::Server::getIndex()
{
	return (this->_index);
}
