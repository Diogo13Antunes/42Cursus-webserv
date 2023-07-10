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
	/*
		Executar o script
		Verificar se existem dados até terminar o script
		Mudar o estado para escrita
	*/
}

EventType CGIHandler::getHandleType(void)
{
	return (CGI_EVENT);
}