#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "ServerConfig.hpp"

class ConfigsData
{
	private:
		std::vector<ServerConfig>		_servers;

		void	_allocServersMemory(std::vector<std::string> &src);

	public:
		ConfigsData(void);
		~ConfigsData(void);

		void						setupConfigs(std::vector<std::string> &src);
		const std::vector<ServerConfig>	&getServers(void);

		class InvalidConfigFileException: public std::exception
		{
			public:
				const char *what() const throw();
		};
};
