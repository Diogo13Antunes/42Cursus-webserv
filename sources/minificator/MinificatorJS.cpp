#include "MinificatorJS.hpp"

std::string	MinificatorJS::getMinificatedJS(const char *file)
{
	std::string	minificatedFile;

	minificatedFile = getFile(file);

	MinificatorUtils::removeInlineComents(minificatedFile, "//");
	MinificatorUtils::removeNewLineChars(minificatedFile);
	MinificatorUtils::removeComentsWithDelemiters(minificatedFile, "/*", "*/");
	return (minificatedFile);
}