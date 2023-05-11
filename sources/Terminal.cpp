#include "Terminal.hpp"

// Used to print messages of error to the standart error
void	Terminal::printErrors(const char *error)
{
	std::cerr << "Error: " << error << std::endl;
}

// Used to print messages to the standart output
void	Terminal::printMessages(const char *msg)
{
	std::cout << msg << std::endl;
}
