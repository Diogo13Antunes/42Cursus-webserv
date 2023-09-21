/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:51:15 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/21 11:41:09 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "configs.hpp"
#include "SocketUtils.hpp"
#include "Signals.hpp"

#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


static void debugPrint(struct sockaddr_in *address);
static void debugServersPrint(std::vector<int> servers);
static void debugServersEndpointPrint(std::vector<std::string> endpoints);

Server::Server(void): _configs(NULL){}

Server::~Server(void)
{
	std::cout << std::endl;
	std::cout << BOLDRED << "Webserv: Server shutdown" << RESET << std::endl;
}

void Server::setConfigs(ConfigsData *configs)
{
	_configs = configs;
}

bool Server::init(void)
{
	if (!_initServers(_configs->getServers()))
		return (false);
	if (!_initEventLoop())
		return (false);
	_initConnections();
	_initEventDemux();
	_printActiveEndpoins();
	return (true);
}

void Server::start(void)
{
	while (true)
	{
		_connections.updateAllConnections();
		_eventDemux.waitAndDispatchEvents();
		_eventLoop.handleEvents();
		if (Signals::isStopSignalTriggered())
			break ;
	}
}

bool Server::_initServers(std::vector<ServerConfig>& serverConfigs)
{
	std::vector<ServerConfig>::iterator	it;
	std::string							port;
	std::string							host;
	int									serverFd;

	for (it = serverConfigs.begin(); it != serverConfigs.end(); it++)
	{
		host = (*it).getHost();
		port = (*it).getPort();
		it->setIp(SocketUtils::getIpAddress(host, port));
		if (_isServerAlreadyInitialized(host, port))
			continue ;
		serverFd = _initAndStoreSocketInf(host, port);
		if (serverFd == -1)
		{
			_printIniServerError(host, port);
			return (false);
		}
		port = SocketUtils::getPort(serverFd);
		_addNewServerEndpoint(host, port);
		it->setPort(port);
	}
	return (true);
}

bool Server::_initEventLoop(void)
{
	try {
		_eventLoop.setMessenger(&_messenger);
		_eventLoop.registerEventHandler(new ReadSocketHandler(new HandleReq(_configs)));
		_eventLoop.registerEventHandler(new WriteHandler(new HandleRes()));
		_eventLoop.registerEventHandler(new ReadCgiHandler());
		_eventLoop.registerEventHandler(new WriteCgiHandler());
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << BOLDRED << "Webserv: Server Initialization Failed - Memory Allocation Error" 
				<< RESET << std::endl;
		return (false);
	} 
	catch (const std::exception& e)
	{
		std::cout << BOLDRED << "Webserv: Server Initialization Failed - " 
				<< e.what() << RESET << std::endl;
		return (false);
	}
	return (true);
}

void Server::_initConnections(void)
{
	_connections.setMessenger(&_messenger);
}

void Server::_initEventDemux(void)
{
	_eventDemux.init(_serversInfo);
	_eventDemux.setMessenger(&_messenger);
}

int Server::_initAndStoreSocketInf(std::string host, std::string port)
{
	struct addrinfo		hints, *result;
	struct sockaddr_in	address;
	int					serverFd;
	int 				enable;

    memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (!_isValidPort(port))
		return (-1);
	if (getaddrinfo(host.c_str(), port.c_str(), &hints, &result) != 0)
		return (-1);
	memset((char *)&address, 0, sizeof(address));
	address = *((struct sockaddr_in *)(result->ai_addr));
	if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		freeaddrinfo(result);
		return (-1); 
	}
	enable = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		close(serverFd);
		freeaddrinfo(result);
		return (-1);
	}
	if (bind(serverFd, (struct sockaddr *) &address, sizeof(address)) < 0) 
	{
		close(serverFd);
		freeaddrinfo(result);
    	return (-1);
	}
    if (listen(serverFd, DEFAULT_BACKLOG) < 0)
    {
		close(serverFd);
		freeaddrinfo(result);
        return (-1);
    }
	freeaddrinfo(result);
	_serversInfo.insert(std::make_pair(serverFd, address));
	return (serverFd);
}

bool Server::_isServerAlreadyInitialized(std::string host, std::string port)
{
	struct addrinfo						hints, *result;
	std::vector<std::string>::iterator	it;
	std::string							server;
	std::string							ip;

	ip = SocketUtils::getIpAddress(host, port);
	for (it = _serverEndpoints.begin(); it !=_serverEndpoints.end(); it++)
	{
		if (!it->compare(host + ":" + port) || !it->compare(ip + ":" + port))
			return (true);
	}
	return (false);
}

void Server::_addNewServerEndpoint(std::string host, std::string port)
{
	std::string	server;

	server = host + ":" + port;
	_serverEndpoints.push_back(server);	
}

void Server::_printIniServerError(std::string host, std::string port)
{
	std::cout << BOLDRED << "WebServer: Failed to Initialize Server on ";
	std::cout << BOLDWHITE << host << ":" << port << RESET <<std::endl;
}

void Server::_printActiveEndpoins(void)
{
	std::vector<std::string>::iterator it;

	for (it = _serverEndpoints.begin(); it != _serverEndpoints.end(); it++)
	{
		std::cout << GREEN << "Webserv: Server started on ";
		std::cout << BOLDWHITE << "http://" << (*it) << RESET << std::endl;
	}
}

bool Server::_isValidPort(std::string port) 
{
	std::stringstream	ss;
	int					portInt;
	bool				res;

	ss << port;
	ss >> portInt;
	res = portInt >= MIN_PORT_VALUE && portInt <= MAX_PORT_VALUE;
	return (res);
}

// DEBUG
static void debugPrint(struct sockaddr_in *address)
{
	std::cout << "sin_family: " << address->sin_family << std::endl;
    std::cout << "sin_port: " << ntohs(address->sin_port) << std::endl;
    std::cout << "sin_addr: " << inet_ntoa(address->sin_addr) << std::endl;
}

static void debugServersPrint(std::vector<int> servers)
{
	std::vector<int>::iterator it;

	std::cout << "List of Servers" << std::endl;
	for (it = servers.begin(); it != servers.end(); it++)
		std::cout << "fd: " << *it << std::endl;
}

static void debugServersEndpointPrint(std::vector<std::string> endpoints)
{
	std::vector<std::string>::iterator it;

	std::cout << "List of Servers" << std::endl;
	for (it = endpoints.begin(); it != endpoints.end(); it++)
		std::cout << *it << std::endl;
}
