#include "Server.hpp"

Server::Server(void): _port(0)
{
	//Default Server Constructor
}

Server::Server(const Server &src)
{
	//Server Copy Constructor
	*this = src;
}

Server::~Server(void)
{
	//Default Server Destructor
}

Server &Server::operator=(const Server &src)
{
	//Server Copy Assignment Operator
	
	_port = src._port;
	_serverName = src._serverName;
	_root = src._root;
	_index = src._index;
	return (*this);
}

void	Server::setPort(int newPort)
{
	this->_port = newPort;
}

void	Server::setServerName(std::string newServerName)
{
	this->_serverName = newServerName;
}

void	Server::setRoot(std::string newRoot)
{
	this->_root = newRoot;
}

void	Server::setIndex(std::string newIndex)
{
	this->_index = newIndex;
}

int	Server::getPort()
{
	return (this->_port);
}

std::string	Server::getServerName()
{
	return (this->_serverName);
}

std::string	Server::getRoot()
{
	return (this->_root);
}

std::string	Server::getIndex()
{
	return (this->_index);
}
