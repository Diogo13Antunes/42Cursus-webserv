#include "ConfigsData.hpp"

static size_t							getNumberOfIdentations(std::string &line);
static bool								isInsideServer(std::string &src);
static std::pair<size_t, std::string>	createPair(size_t lineNbr, std::string lineContent);

ConfigsData::ConfigsData(void)
{
	//Default ConfigsData Constructor
}

ConfigsData::~ConfigsData(void)
{
	//Default ConfigsData Destructor
}

void	ConfigsData::setupConfigs(std::map<size_t, std::string> &fileContent)
{
	std::map<size_t, std::string>::iterator	it;
	std::string								line;
	std::map<size_t, std::string>			serverConf;

	_allocServersMemory(fileContent);
	it = fileContent.begin();
	while (it != fileContent.end())
	{
		line = it->second;
		if (line.compare("server:") == 0)
		{
			it++;
			while (it != fileContent.end() && isInsideServer(it->second))
			{
				serverConf.insert(createPair(it->first, it->second));
				it++;
			}
			_servers.push_back(ServerConfig(serverConf));
			serverConf.clear();
		}
	}
	for (size_t i = 0; i < _servers.size(); i++)
	{
		if (_servers.at(i).getConfigError() == false)
		{
			std::string msg;
			msg = _servers.at(i).getConfigErrorMessage();
			throw InvalidConfigFileDataException(msg);
		}
	}
}

std::vector<ServerConfig>	&ConfigsData::getServers(void)
{
	return (_servers);
}

/* PRIVATE METHODS */

void	ConfigsData::_allocServersMemory(std::map<size_t, std::string> &fileContent)
{
	std::map<size_t, std::string>::iterator	it;
	size_t								serverCount;

	serverCount = 0;
	for (it = fileContent.begin(); it != fileContent.end(); it++)
	{
		if (getNumberOfIdentations(it->second) == 0)
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

static std::pair<size_t, std::string>	createPair(size_t lineNbr, std::string lineContent)
{
	return (std::make_pair<size_t, std::string>(lineNbr, lineContent));
}

/* EXCEPTIONS */

ConfigsData::InvalidConfigFileDataException::InvalidConfigFileDataException(std::string msg):
	_msg(msg), _fullMsg(NULL)
{
	std::string str;

	str = "WebServ: ";
	str += _msg;

	_fullMsg = new char[str.size() + 1];
	_fullMsg[str.size()] = '\0';
	std::strcpy(_fullMsg, str.c_str());
}

ConfigsData::InvalidConfigFileDataException::~InvalidConfigFileDataException() throw()
{
	delete[] _fullMsg;
}

const char *ConfigsData::InvalidConfigFileDataException::what() const throw()
{
	return (_fullMsg);
}

// Just for debug
/*
#include <stdexcept>
#include <iostream>
ConfigsData::ConfigsData(const ConfigsData &src)
{
	throw std::runtime_error("ConfigsData: No copies are allowed");
	*this = src;
}

ConfigsData& ConfigsData::operator=(const ConfigsData &src)
{
	throw std::runtime_error("ConfigsData: No copies are allowed");
	return (*this);
}
*/