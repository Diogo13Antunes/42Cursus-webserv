#include "ExecCgiState.hpp"

#include "Terminal.hpp"

ExecCgiState::ExecCgiState(void)
{
	//Default ExecCgiState Constructor
}

ExecCgiState::~ExecCgiState(void)
{
	//Default ExecCgiState Destructor
}

/*
	Criar estado de erro para apanhar as excessoews do executer.
*/
#include <cstdlib>

StateCgiType ExecCgiState::handle(Event *event)
{
	CGIExecuter	*ex;

	ex = event->getCgiEx();

	ex->execute("cgi-bin/cgi_script.py", "Hi From Python");

	return (GETTING_DATA_CGI);
}
