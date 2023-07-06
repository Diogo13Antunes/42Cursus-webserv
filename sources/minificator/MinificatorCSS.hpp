#pragma once

#include "AMinificator.hpp"

class MinificatorCSS: public AMinificator
{
	public:
		static std::string	getMinificatedCSS(const char *file);

};
