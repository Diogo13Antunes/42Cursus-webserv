#pragma once

#include "AMinificator.hpp"

class MinificatorJS: public AMinificator
{
	public:
		static std::string	getMinificatedJS(const char *file);
};
