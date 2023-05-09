#pragma once

#include <string>

class Server
{
	public:

		void		setPort(int	newPort);
		void		setServerName(std::string newServerName);
		void		setRoot(std::string newRoot);
		void		setIndex(std::string newIndex);

		int			getPort();
		std::string	getServerName();
		std::string	getRoot();
		std::string	getIndex();

		Server &operator=(const Server &src);
		Server(const Server &src);
		Server(void);
		~Server(void);

	private:

		int			_port;
		std::string	_serverName;
		std::string	_root;
		std::string	_index;
};
