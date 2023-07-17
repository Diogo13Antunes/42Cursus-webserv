#include "CGIHandler.hpp"
// #include "CGIExecuter.hpp"
#include "IEventHandler.hpp"

#include <iostream>

CGIHandler::CGIHandler(void): IEventHandler()
{
	//Default CGIHandler Constructor
	_handleCgi = NULL;	
}

CGIHandler::CGIHandler(HandleCgi *handleCgi):
	IEventHandler(),
	_handleCgi(handleCgi)
{

}

CGIHandler::~CGIHandler(void)
{
	//Default CGIHandler Destructor
}

void CGIHandler::handleEvent(Event *event)
{
	std::cout << "CGI Handler" << std::endl;

	_handleCgi->setEvent(event);

	_handleCgi->handle();

	if (_handleCgi->isCgiFinished())
	{
		Terminal::printMessages("Terminou CGI");	
		event->setState(CGI_EVENT_COMPLETE);
	}
}

EventType CGIHandler::getHandleType(void)
{
	return (CGI_EVENT);
}