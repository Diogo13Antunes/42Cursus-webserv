#include "MinificatorHTML.hpp"

static void	removeNewLineChars(std::string &src);
static void	removeComents(std::string &src);

MinificatorHTML::MinificatorHTML(const char *file):
	AMinificator(file)
{
	_minificatedFile = _fileContent;

	MinificatorUtils::removeNewLineChars(_minificatedFile);
	MinificatorUtils::removeComentsWithDelemiters(_minificatedFile, "<!--", "-->");
}

MinificatorHTML::~MinificatorHTML(void)
{
	//Default MinificatorHTML Destructor
}

std::string	MinificatorHTML::getMinificatedHTML(void)
{
	return (_minificatedFile);
}
