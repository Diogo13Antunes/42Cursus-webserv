#include "Configs.hpp"

static bool			initConfigs(char *configFile);
static std::string	getString();

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
static bool	initConfigs(char *configFile)
{
	std::ifstream	file(configFile);
	std::string		buff;
	std::string		contentFromFile;

	if (file.is_open())
	{
		Terminal::printMessages("File opened successfully");
		while (std::getline(file, buff))
				contentFromFile += buff;
		Terminal::printMessages("File ->");
		Terminal::printMessages(contentFromFile.c_str());


	}
	else
	{
		Terminal::printErrors("Impossible to read from Configuration File");
		return (false);
	}
	return (true);
}

char	Configs::getNextToken()
{
	static size_t	index = 0;
	char			temp = 0;

	while (1)
	{
		temp = this->_configFile.c_str()[index];
		if (temp == '\0')
			break;
		else if (temp == TOKEN_CURLY_OPEN)
			return (TOKEN_CURLY_OPEN);
		else if (temp == TOKEN_CURLY_CLOSE)
			return (TOKEN_CURLY_CLOSE);
		else if (temp == TOKEN_ARRAY_OPEN)
			return (TOKEN_ARRAY_OPEN);
		else if (temp == TOKEN_ARRAY_CLOSE)
			return (TOKEN_ARRAY_CLOSE);
		else if (temp == TOKEN_COMMA)
			return (TOKEN_COMMA);
		else if (temp == TOKEN_COLON)
			return (TOKEN_COLON);
		index++;
	}
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

	i = *index;
	result.clear();
	while (1)
	{
		temp = 
	}
	*index = i + 1;
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
