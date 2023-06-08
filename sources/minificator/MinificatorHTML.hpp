#pragma once

#include "AMinificator.hpp"

class MinificatorHTML: public AMinificator
{
	private:

		std::string		_minificatedFile;

	public:

		MinificatorHTML(const char *file);
		~MinificatorHTML(void);

		std::string		getMinificatedHTML(void);
};
