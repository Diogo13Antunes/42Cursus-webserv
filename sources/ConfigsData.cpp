#include "ConfigsData.hpp"

ConfigsData::ConfigsData(void)
{
	//Default ConfigsData Constructor
	_dataInt.insert(std::pair<std::string, int>("listen", 0));
	_dataStr.insert(std::pair<std::string, std::string>("server_name", ""));
	_dataStr.insert(std::pair<std::string, std::string>("root", ""));
	_dataStr.insert(std::pair<std::string, std::string>("index", ""));
}

ConfigsData::~ConfigsData(void)
{
	//Default ConfigsData Destructor
}

void	ConfigsData::addNewConfigs(std::string name, std::string data)
{
	std::map<std::string, std::string>::iterator	itStr;
	std::map<std::string, int>::iterator			itInt;

	itStr = _dataStr.find(name);
	itInt = _dataInt.find(name);
	if (itStr != _dataStr.end())
		(*itStr).second = data;
	else if (itInt != _dataInt.end())
		(*itInt).second = ConfigsUtils::strToInt(data);
	else
		throw InvalidConfigDataException();
}

int	ConfigsData::getListen(void)
{
	return (_dataInt.find("listen")->second);
}

std::string	ConfigsData::getServerName(void)
{
	return (_dataStr.find("server_name")->second);
}

std::string	ConfigsData::getRoot(void)
{
	return (_dataStr.find("root")->second);
}

std::string	ConfigsData::getIndex(void)
{
	return (_dataStr.find("index")->second);
}

/* Exceptions */

const char *ConfigsData::InvalidConfigDataException::what(void) const throw()
{
	return ("InvalidConfigDataException: Invalid Data Type");
}
