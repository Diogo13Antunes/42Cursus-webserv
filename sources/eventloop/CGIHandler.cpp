#include "CGIHandler.hpp"
#include "IEventHandler.hpp"

#include <iostream>

CGIHandler::CGIHandler(void)
{
	//Default CGIHandler Constructor
}

CGIHandler::~CGIHandler(void)
{
	//Default CGIHandler Destructor
}

void CGIHandler::handleEvent(Event *event)
{
	std::cout << "CGI Handler" << std::endl;
}

EventType CGIHandler::getHandleType(void)
{
	return (CGI_EVENT);
}