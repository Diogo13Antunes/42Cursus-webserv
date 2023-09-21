#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>

#include "ServerConfig.hpp"

class ConfigsData
{
	private:
		std::vector<ServerConfig>		_servers;

		void	_allocServersMemory(std::map<size_t, std::string> &fileContent);

	public:
		ConfigsData(void);
		~ConfigsData(void);

		void						setupConfigs(std::map<size_t, std::string> &fileContent);
		std::vector<ServerConfig>	&getServers(void);

		class InvalidConfigFileDataException: public std::exception
		{
			private:
				std::string _msg;
				char		*_fullMsg;

			public:
				InvalidConfigFileDataException(std::string msg);
				virtual ~InvalidConfigFileDataException() throw();

				const char *what() const throw();
		};
};
