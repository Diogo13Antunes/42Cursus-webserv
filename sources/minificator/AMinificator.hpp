#pragma once

#include <iostream>

#include "Terminal.hpp"
#include "MinificatorUtils.hpp"

class AMinificator
{
	protected:

		std::string	_fileContent;

	public:

		AMinificator(const char *file);
		AMinificator(void);
		~AMinificator(void);

};
