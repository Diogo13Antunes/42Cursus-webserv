#pragma once

#include <IStateCGI.hpp>
#include <map>

#include "ExecCgiState.hpp"
#include "GettingDataCgiState.hpp"

class HandleCgi
{
	private:
		std::map<StateCgiType, IStateCGI*>	_stateMap;
		Event								*_event;

	public:
		HandleCgi(void);
		~HandleCgi(void);
		
		void	setEvent(Event *event);
		void	handle(void);
		bool	isCgiFinished(void);

};
