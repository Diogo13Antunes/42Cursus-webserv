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

#include <cstdlib>

void printState(StateCgiType state)
{
	std::string msg;

	msg = "Estado do CGI - ";
	switch (state)
	{
		case EXEC_CGI:
			msg += "EXEC_CGI";
			break;
		case GETTING_DATA_CGI:
			msg += "GETTING_DATA_CGI";
			break;
		case END_CGI:
			msg += "END_CGI";
			break;
		default:
			break;
	}

	Terminal::printMessages(msg.c_str());
}

void CGIHandler::handleEvent(Event *event)
{
	std::cout << "CGI Handler" << std::endl;

	_handleCgi->setEvent(event);

	printState(event->getCgiState());

	_handleCgi->handle();

	//printState(event->getCgiState());

	if (_handleCgi->isCgiFinished())
	{
		Terminal::printMessages("Terminou CGI");
		event->setState(WRITE_EVENT);
	}

	// std::exit(0); // Remover depois dos testes.

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