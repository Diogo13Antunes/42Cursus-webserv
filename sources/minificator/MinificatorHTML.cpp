#include "MinificatorHTML.hpp"

static void	removeNewLineChars(std::string &src);
static void	removeComents(std::string &src);

MinificatorHTML::MinificatorHTML(const char *file):
	AMinificator(file)
{
	_minificatedFile = _fileContent;

	removeNewLineChars(_minificatedFile);
	removeComents(_minificatedFile);

	std::cout << _minificatedFile << std::endl;

}

MinificatorHTML::~MinificatorHTML(void)
{
	//Default MinificatorHTML Destructor
}

std::string	MinificatorHTML::getMinificatedHTML(void)
{
	return (_minificatedFile);
}

static void	removeNewLineChars(std::string &src)
{
	std::string result;
	std::string	line;
	size_t		i = 0;
	size_t		j = 0;

	while (1)
	{
		i = src.find_first_of("\n", j);
		if (i == src.npos)
			break;
		line = src.substr(j, i - j);
		if (line.find_first_not_of(WHITE_SPACE) != line.npos)
			result += MinificatorUtils::stringTrim(line) + " ";
		i++;
		j = i;
	}
	src = result;
}

static void	removeComents(std::string &src)
{
	std::string result;
	size_t		start = 0;
	size_t		end = 0;
	size_t		index = 0;

	while (1)
	{
		start = src.find("<!--", index);
		end = src.find("-->", start);
		if (start == src.npos || end == src.npos)
		{
			result += src.substr(index, src.size() - index + 1);
			break;
		}
		result += src.substr(index, start - index);
		index = end + 4;
	}
	src = result;
}
