#include "AMinificator.hpp"

std::string	AMinificator::getFile(const char *file)
{
	std::string	fileContent;

	fileContent = MinificatorUtils::getFileContent(file);
	if (fileContent.empty())
		std::cerr << "Invalid File" << std::endl;
	return (fileContent);
}
