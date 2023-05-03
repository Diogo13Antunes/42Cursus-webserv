#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <Terminal.hpp>

class Configs
{
	public:
		Configs &operator=(const Configs &src);
		Configs(const Configs &src);
		Configs(void);
		~Configs(void);

	private:

		int			_port;
		std::string	_serverName;
		std::string	_root;
		std::string	_index;
};
