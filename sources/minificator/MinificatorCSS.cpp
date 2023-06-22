#include "MinificatorCSS.hpp"

std::string		MinificatorCSS::getMinificatedCSS(const char *file)
{
	std::string	minificatedFile;

	minificatedFile = getFile(file);
	MinificatorUtils::removeNewLineChars(minificatedFile);
	MinificatorUtils::removeComentsWithDelemiters(minificatedFile, "/*", "*/");
	return (minificatedFile);
}
