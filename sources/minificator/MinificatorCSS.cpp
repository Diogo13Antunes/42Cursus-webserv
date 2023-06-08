#include "MinificatorCSS.hpp"

MinificatorCSS::MinificatorCSS(const char *file):
	AMinificator(file)
{
	_minificatedFile = _fileContent;

	MinificatorUtils::removeNewLineChars(_minificatedFile);
	MinificatorUtils::removeComentsWithDelemiters(_minificatedFile, "/*", "*/");
}

MinificatorCSS::~MinificatorCSS(void)
{
	//Default MinificatorCSS Destructor
}

std::string		MinificatorCSS::getMinificatedCSS(void)
{
	return (_minificatedFile);
}
