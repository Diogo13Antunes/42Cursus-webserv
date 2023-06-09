#include "ConfigsData.hpp"

ConfigsData::ConfigsData(void)
{
	//Default ConfigsData Constructor
	//_dataInt.insert(std::pair<std::string, int>("listen", 0));
	//_dataStr.insert(std::pair<std::string, std::string>("server_name", ""));
	//_dataStr.insert(std::pair<std::string, std::string>("root", ""));
	//_dataStr.insert(std::pair<std::string, std::string>("index", ""));
	//_initNewDataArray("error_page");
}

ConfigsData::~ConfigsData(void)
{
	//Default ConfigsData Destructor
}

/* void	ConfigsData::addNewConfigs(std::string name, std::string data)
{
	std::map<std::string, std::string>::iterator									itStr;
	std::map<std::string, int>::iterator											itInt;
	std::map<std::string, std::map<std::string, std::string> >::iterator			itArrs;

	itStr = _dataStr.find(name);
	itInt = _dataInt.find(name);
	itArrs = _dataArrs.find(name);
	if (itStr != _dataStr.end())
		(*itStr).second = ConfigsUtils::removeQuotes(data);
	else if (itInt != _dataInt.end())
		(*itInt).second = ConfigsUtils::strToInt(data);
	else if (itArrs != _dataArrs.end())
	{
		std::map<std::string, std::string>				&innerMap = (*itArrs).second;
		std::map<std::string, std::string>				temp;
		std::map<std::string, std::string>::iterator	itTemp;
		temp = _newArrayConfig(data);
		if (!temp.empty())
		{
			for (itTemp = temp.begin(); itTemp != temp.end(); ++itTemp)
				innerMap.insert(*itTemp);
		}
		std::cout << "[Key] : [Value]" << std::endl;
		for (itTemp = temp.begin(); itTemp != temp.end(); ++itTemp)
			std::cout << "[" << (*itTemp).first << "] : [" << (*itTemp).second << "]" << std::endl;
	}
	else
		throw InvalidConfigDataException();
} */

void	ConfigsData::addNewConfigs(std::string name, std::string data)
{
	std::map<std::string, std::string>::iterator									itStr;
	std::map<std::string, int>::iterator											itInt;
	std::map<std::string, std::map<std::string, std::string> >::iterator			itArrs;

	/*itStr = _dataStr.find(name);
	if (itStr != _dataStr.end())
	{
		(*itStr).second = ConfigsUtils::removeQuotes(data);
		return;
	}*/

	_dataStr.insert(std::pair<std::string, std::string>(name, ConfigsUtils::removeQuotes(data)));

	return;

	itInt = _dataInt.find(name);
	if (itInt != _dataInt.end())
	{
		(*itInt).second = ConfigsUtils::strToInt(data);
		return;
	}
	itArrs = _dataArrs.find(name);
	if (itArrs != _dataArrs.end())
	{
		std::map<std::string, std::string>				&innerMap = (*itArrs).second;
		std::map<std::string, std::string>				temp;
		std::map<std::string, std::string>::iterator	itTemp;
		temp = _newArrayConfig(data);
		if (!temp.empty())
		{
			for (itTemp = temp.begin(); itTemp != temp.end(); ++itTemp)
				innerMap.insert(*itTemp);
		}
		// std::cout << "[Key] : [Value]" << std::endl;
		// for (itTemp = temp.begin(); itTemp != temp.end(); ++itTemp)
			// std::cout << "[" << (*itTemp).first << "] : [" << (*itTemp).second << "]" << std::endl;
		return;
	}
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

std::string ConfigsData::getConfig(std::string name)
{
	std::map<std::string, std::string>::iterator	it;
	std::string										res;

	it = _dataStr.find(name);
	if (it != _dataStr.end())
		res = it->second;
	return(res);
}

void	ConfigsData::_initNewDataArray(std::string key)
{
	std::map<std::string, std::string>	innerArray;
	_dataArrs.insert(std::make_pair(key, innerArray));
}

std::map<std::string, std::string>	ConfigsData::_newArrayConfig(std::string &src)
{
	std::map<std::string, std::string>	newArray;
	std::string							key;
	std::string							value;
	std::string							temp;
	size_t								i = 1;

	while (src[i])
	{
		while (src[i] != ',' && src[i + 1])
			temp += src[i++];
		temp = ConfigsUtils::removeQuotes(ConfigsUtils::stringTrim(temp));
		if (ConfigsUtils::isSingleColon(temp))
		{
			key = ConfigsUtils::stringTrim(temp.substr(0, temp.find_first_of(":")));
			value = ConfigsUtils::stringTrim(temp.substr(temp.find_first_of(":") + 1, temp.size()));
			newArray.insert(std::pair<std::string, std::string>(key, value));
		}
		else
		{
			newArray.clear();
			return (newArray);
		}
		temp.clear();
		i++;
	}
	return (newArray);
}

/* Exceptions */

const char *ConfigsData::InvalidConfigDataException::what(void) const throw()
{
	return ("InvalidConfigDataException: Invalid Data Type");
}
