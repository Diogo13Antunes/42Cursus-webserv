#pragma once

#include <string>
#include <iostream>
#include <map>

#include "Terminal.hpp"
#include "ConfigsUtils.hpp"

class ConfigsData
{
	private:

		std::map<std::string, std::string>									_dataStr;
		std::map<std::string, int>											_dataInt;
		std::map<std::string, std::map<std::string, std::string> >			_dataArrs;

		void																_initNewDataArray(std::string key);
		std::map<std::string, std::string>									_newArrayConfig(std::string &src);

	public:

		ConfigsData(void);
		~ConfigsData(void);

		int			getListen(void);
		std::string	getServerName(void);
		std::string	getRoot(void);
		std::string	getIndex(void);

		std::string getConfig(std::string name);

		void		addNewConfigs(std::string name, std::string data);

		class InvalidConfigDataException: public std::exception
		{
			public:
				const char *what() const throw();
		};
};
