#include "GettingDataCgiState.hpp"

GettingDataCgiState::GettingDataCgiState(void)
{
	//Default GettingDataCgiState Constructor
}

GettingDataCgiState::~GettingDataCgiState(void)
{
	//Default GettingDataCgiState Destructor
}

#include <cstdlib>
StateCgiType GettingDataCgiState::handle(Event *event)
{
	int			fd;
	char		buffer[SIZE_BUFFER];
	int			nRead;
	std::string	src;

	fd = event->getCgiFd();

	bzero(buffer, SIZE_BUFFER);
	nRead = read(fd, buffer, SIZE_BUFFER - 1);
	src = buffer;

	event->updateCgiScriptResult(src);

	std::cout << event->getCgiScriptResult() << std::endl;

	/* if (nRead <= 0)
	{
		std::cout << "Terminou de ler o FD" << std::endl;
		std::exit(0);
		return (END_CGI);
	} */

	if (event->getCgiEx()->isEnded())
	{
		std::cout << "Terminou de ler o FD" << std::endl;
		std::exit(0);
		return (END_CGI);
	}
	return (event->getCgiState());
}
