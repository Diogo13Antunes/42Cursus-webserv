#include "GettingDataCgiState.hpp"

#include "EventType.hpp"

GettingDataCgiState::GettingDataCgiState(void)
{
	//Default GettingDataCgiState Constructor
}

GettingDataCgiState::~GettingDataCgiState(void)
{
	//Default GettingDataCgiState Destructor
}

StateCgiType GettingDataCgiState::handle(Event *event)
{
	CGIExecuter	*cgi;
	int			fd;
	char		buffer[SIZE_BUFFER];
	int			nRead;
	std::string	src;

	static int count = 0;


	/*
	std::cout << "GettingDataCgiState: handle" << std::endl;

	std::cout << "INICIO" << std::endl;
	for(int i = 0; i < 99999999; i++);
	std::cout << "TERMINOU" << std::endl;
	*/

	cgi = event->getCgiEx();
	fd = event->getCgiFd();

	//bzero(buffer, SIZE_BUFFER);
	nRead = read(fd, buffer, SIZE_BUFFER - 1);
	//buffer[nRead] = 0;

	if (nRead <= 0)
	{
		//std::cout << "GettingDataCgiState: fALHOU NA LEITURA" << std::endl;
		event->setState(CLOSED_EVENT);
	}
	
	src = buffer;

	event->updateCgiScriptResult(src);



	if (cgi->isEnded())
	{
		//std::cout << "GettingDataCgiState: handle: isEnded(): true" << std::endl;
		//close(fd);
		return (END_CGI);
	}

	//std::cout << "GettingDataCgiState: return: state: " << event->getCgiState() << std::endl;
	return (event->getCgiState());
}
