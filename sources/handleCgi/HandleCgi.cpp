#include "HandleCgi.hpp"

HandleCgi::HandleCgi(void)
{
	//Default HandleCgi Constructor
	_stateMap.insert(std::make_pair(EXEC_CGI, new ExecCgiState()));
	_stateMap.insert(std::make_pair(GETTING_DATA_CGI, new GettingDataCgiState()));
}

HandleCgi::~HandleCgi(void)
{
	std::map<StateCgiType, IStateCGI*>::iterator	it;

	for (it = _stateMap.begin(); it != _stateMap.end(); it++)
	{
		if (it->second)
			delete it->second;
	}
}

void	HandleCgi::setEvent(Event *event)
{
	_event = event;
}

void	HandleCgi::handle(void)
{
	std::map<StateCgiType, IStateCGI*>::iterator	it;
	StateCgiType									state;

	state = _event->getCgiState();

	it = _stateMap.find(state);
	if (it != _stateMap.end())
		state = it->second->handle(_event);

	_event->setCgiState(state);
}

bool	HandleCgi::isCgiFinished(void)
{
	if (_event->getCgiState() == END_CGI)
		return (true);
	return (false);
}
