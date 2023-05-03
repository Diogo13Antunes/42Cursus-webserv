#include <Configs.hpp>

Configs::Configs(void)
{
	//Default Configs Constructor
}

Configs::Configs(const Configs &src)
{
	//Configs Copy Constructor
}

Configs::~Configs(void)
{
	//Default Configs Destructor
}

Configs &Configs::operator=(const Configs &src)
{
	//Configs Copy Assignment Operator
}

// Return true if the configs were done well, if not return false
static bool	initConfigs(char *configFile)
{
	std::ifstream	file(configFile);
	std::string		buff;
	std::string		contentFromFile;

	if (file.is_open())
	{
		Terminal::printMessages)("File opened successfully");
		while (std::getline(file, buff))
				contentFromFile += buff;
		Terminal::printMessages("File ->");
		Terminal::printMessages("");
		Terminal::printMessages(contentFromFile.c_str());
	}
	else
	{
		Terminal::printErrors("Impossible to read from Configuration File");
		return (false);
	}
	return (true);
}