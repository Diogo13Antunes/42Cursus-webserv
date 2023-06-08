#pragma once

#include "AMinificator.hpp"

class MinificatorCSS: public AMinificator
{
	private:

		std::string		_minificatedFile;


	public:

		MinificatorCSS(const char *file);
		~MinificatorCSS(void);

		std::string		getMinificatedCSS(void);

};
