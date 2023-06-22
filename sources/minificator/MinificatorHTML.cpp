#include "MinificatorHTML.hpp"

std::string	MinificatorHTML::getMinificatedHTML(const char *file)
{
	std::string	minificatedFile;

	minificatedFile = getFile(file);
	MinificatorUtils::removeNewLineChars(minificatedFile);
	MinificatorUtils::removeComentsWithDelemiters(minificatedFile, "<!--", "-->");
	return (minificatedFile);
}
