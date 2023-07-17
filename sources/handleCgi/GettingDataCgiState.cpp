#include "GettingDataCgiState.hpp"

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

	cgi = event->getCgiEx();
	fd = event->getCgiFd();

	bzero(buffer, SIZE_BUFFER);
	nRead = read(fd, buffer, SIZE_BUFFER - 1);
	src = buffer;

	event->updateCgiScriptResult(src);

	if (cgi->isEnded())
	{
		//close(fd);
		return (END_CGI);
	}
	return (event->getCgiState());
}
