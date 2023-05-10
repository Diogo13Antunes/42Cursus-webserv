#pragma once

#include <string>
#include <iostream>

#include "Terminal.hpp"
#include "Server.hpp"

class ConfigsData
{
	public:

		Server	_serverData;
		
		ConfigsData &operator=(const ConfigsData &src);
		ConfigsData(const ConfigsData &src);
		ConfigsData(void);
		~ConfigsData(void);
	
	private:

		
};
