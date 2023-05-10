#pragma once

#include <string>
#include <map>

/* class Server
{
	private:

		std::map<>

		int			_port;
		std::string	_serverName;
		std::string	_root;
		std::string	_index;

	public:

		Server(const Server &src);
		Server(void);
		~Server(void);

		Server			&operator=(const Server &src);

		void			setPort(unsigned int newPort);
		void			setServerName(std::string newServerName);
		void			setRoot(std::string newRoot);
		void			setIndex(std::string newIndex);

		unsigned int	getPort();
		std::string		getServerName();
		std::string		getRoot();
		std::string		getIndex();

}; */

class Server
{
	private:

		/**
		 * port (int)
		 * keep_alive (str)
		 * server_name (str)
		*/
		std::map<std::string, std::string>	_dataStr;
		std::map<std::string, int>			_dataInt;

	public:

		Server(const Server &src);
		Server(void);
		~Server(void);

		Server			&operator=(const Server &src);

		int				getListen(void);

		bool			addNewConfigs(std::string name, std::string data);

};
