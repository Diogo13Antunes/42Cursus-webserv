#include <Terminal.hpp>

Terminal::Terminal(void)
{
	//Default Terminal Constructor
}

Terminal::~Terminal(void)
{
	//Default Terminal Destructor
}

void	Terminal::printErrors(const char *error)
{
	std::cerr << "Error: " << error << std::endl;
}

void	Terminal::printMessages(const char *msg)
{
	std::cout << msg << std::endl;
}
