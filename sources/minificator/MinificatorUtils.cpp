#include "MinificatorUtils.hpp"

std::string	MinificatorUtils::getFileContent(const char *file)
{
	std::fstream	fd;
	std::string		fileContent;
	std::string		temp;

	fd.open(file, std::ios::in);
	if (!fd.is_open())
		return (fileContent);
	while (std::getline(fd, temp))
		fileContent += temp + "\n";
	fd.close();
	return (fileContent);
}

std::string	MinificatorUtils::stringTrim(const std::string &str)
{
	std::string	trimmed;
	size_t		start;
	size_t		end;
	size_t		len;

	if (str.empty())
		return (str);
	start = str.find_first_not_of(WHITE_SPACE);
	end = str.find_last_not_of(WHITE_SPACE);
	len = end - start + 1;
	trimmed = str.substr(start, len);
	return (trimmed);
}
