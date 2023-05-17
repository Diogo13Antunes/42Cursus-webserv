#include "WriteHandler.hpp"

WriteHandler::WriteHandler(void)
{
	//Default WriteHandler Constructor
}

WriteHandler::WriteHandler(const WriteHandler &src)
{
	//WriteHandler Copy Constructor
}

WriteHandler::~WriteHandler(void)
{
	//Default WriteHandler Destructor
}

/*
WriteHandler &WriteHandler::operator=(const WriteHandler &src)
{
	//WriteHandler Copy Assignment Operator
}
*/

void WriteHandler::handleEvent(void)
{
	std::cout << "handle WRITE event" << std::endl;
}

EventType WriteHandler::getHandleType(void)
{
	return (WRITE);
}
