#include "AMinificator.hpp"

AMinificator::AMinificator(void)
{
	//Default AMinificator Constructor
}

AMinificator::AMinificator(const char *file)
{
	_fileContent = MinificatorUtils::getFileContent(file);
	if (_fileContent.empty())
		std::cerr << "Invalid File" << std::endl;
}

AMinificator::~AMinificator(void)
{
	//Default AMinificator Destructor
}

