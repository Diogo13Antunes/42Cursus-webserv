#pragma once

#include "AMinificator.hpp"

class MinificatorHTML: public AMinificator
{
	public:
		static std::string	getMinificatedHTML(const char *file);
};
