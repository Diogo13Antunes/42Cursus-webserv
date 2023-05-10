#include "Server.hpp"

/* Server::Server(void): _port(0)
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
} */

Server::Server(void)
{
	//Default Server Constructor
	_dataStr.insert(std::pair<std::string, std::string>("keep_alive", NULL));
	_dataStr.insert(std::pair<std::string, std::string>("server_name", NULL));
	_dataInt.insert(std::pair<std::string, int>("port", 0));
}

/* bool	Server::addNewConfigs(std::string name, std::string data)
{
	std::map<std::string, std::string>::iterator	it;

	it = _dataStr.find(name);
	if (it == _dataStr.end())
		return (false);
	(*it).second = data;
	return (true);
}

bool	Server::addNewConfigs(std::string name, int data)
{
	std::map<std::string, int>::iterator	it;

	it = _dataInt.find(name);
	if (it == _dataInt.end())
		return (false);
	(*it).second = data;
	return (true);
} */

bool	Server::addNewConfigs(std::string name, std::string data)
{
	std::map<std::string, std::string>::iterator	itStr;
	std::map<std::string, int>::iterator			itInt;

	itStr = _dataStr.find(name);
	itInt = _dataInt.find(name);
	if (itStr != _dataStr.end())
		(*itStr).second = data;
	else if (itInt != _dataInt.end())
		(*itInt).second = 13;
		// (*itInt).second = std::atoi(data);
	else
		return (false);
	return (true);
}

int	Server::getListen(void)
{
	return (_dataInt.find("listen")->second);
}
