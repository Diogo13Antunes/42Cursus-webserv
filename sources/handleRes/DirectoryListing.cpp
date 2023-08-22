#include "DirectoryListing.hpp"

#include <iostream>

DirectoryListing::DirectoryListing(void) {}

DirectoryListing::~DirectoryListing(void) {}

StateResType DirectoryListing::handle(Event *event, ServerConfig config)
{
	std::cout << "DirectoryListing" << std::endl;

	return (RESPONSE);
}
