#include "ConfigsData.hpp"

static size_t	getNumberOfIdentations(std::string &line);
static bool		isInsideServer(std::string &src);

ConfigsData::ConfigsData(void)
{
	//Default ConfigsData Constructor
}

ConfigsData::~ConfigsData(void)
{
	//Default ConfigsData Destructor
}

void	ConfigsData::setupConfigs(std::vector<std::string> &fileContent)
{
	std::vector<std::string>::iterator	it;
	std::string							line;
	std::vector<std::string>			serverConf;

	_allocServersMemory(fileContent);
	it = fileContent.begin();
	while (it != fileContent.end())
	{
		line = *it;
		if (line.compare("server:") == 0)
		{
			it++;
			while (it != fileContent.end() && isInsideServer(*it))
			{
				serverConf.push_back(*it);
				it++;
			}
			_servers.push_back(ServerConfig(serverConf));
			serverConf.clear();
		}
	}
	for (size_t i = 0; i < _servers.size(); i++)
	{
		if (_servers.at(i).getConfigError() == false)
			throw InvalidConfigFileException();
	}
}

std::vector<ServerConfig>	&ConfigsData::getServers(void)
{
	return (_servers);
}

/* PRIVATE METHODS */

void	ConfigsData::_allocServersMemory(std::vector<std::string> &src)
{
	std::vector<std::string>::iterator	it;
	size_t								serverCount;

	serverCount = 0;
	for (it = src.begin(); it != src.end(); it++)
	{
		if (getNumberOfIdentations(*it) == 0)
			serverCount++;
	}
	_servers.reserve(serverCount);
}

/* STATIC FUNCTIONS */

static bool	isInsideServer(std::string &src)
{
	if (getNumberOfIdentations(src) > 0)
		return (true);
	return (false);
}

static size_t	getNumberOfIdentations(std::string &line)
{
	size_t	index;
	size_t	identations = 0;
	size_t	nbrSpaces = 0;

	if (line.empty())
		return (0);
	index = line.find_first_not_of(" ");
	for (size_t i = 0; i <= index; i++)
	{
		if (nbrSpaces == 2)
		{
			identations++;
			nbrSpaces = 0;
		}
		if (line[i] == ' ')
			nbrSpaces++;
	}
	return (identations);
}

/* EXCEPTIONS */

const char *ConfigsData::InvalidConfigFileException::what(void) const throw()
{
	return ("InvalidConfigFileException: Invalid Config File");
}
