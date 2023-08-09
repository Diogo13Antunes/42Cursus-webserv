/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:51:15 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/09 16:14:54 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "configs.hpp"

#include <iostream>
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

Server::Server(ConfigsData &configs): _configs(configs) {}

Server::~Server(void) {}

bool Server::init(void)
{
	if (!_initServers())
		return (false);
	if (!_initEventLoop())
		return (false);
	if (!_initConnections())
		return (false);
	if (!_initEventDemux())
		return (false);
	_printActiveEndpoins();
	return (true);
}

void Server::start(void)
{

}

void Server::stop(void)
{
	
}

int Server::_getServerFd(std::string host, std::string port)
{
	struct addrinfo		hints, *result;
	struct sockaddr_in	address;
	int					serverFd;
	int 				enable;

    memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
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
	return (serverFd);
}

bool Server::_isServerAlreadyInitialized(std::string host, std::string port)
{
	struct addrinfo						hints, *result;
	std::vector<std::string>::iterator	it;
	std::string							server;
	std::string							ip;

	ip = _getIpAddress(host, port);
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

void Server::_addNewServerFd(int fd)
{
	_serverFds.push_back(fd);
}

void Server::_errorStartServerPrint(std::string host, std::string port)
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

std::string	Server::_getIpAddress(std::string host, std::string port)
{
	struct addrinfo		hints, *result;
	struct sockaddr_in	*ipv4;
	std::string			ip;

    memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(host.c_str(), port.c_str(), &hints, &result) != 0)
		return ip;
	if (result->ai_family == AF_INET)
	{
		ipv4 = (struct sockaddr_in *)result->ai_addr;
		ip = inet_ntoa(ipv4->sin_addr);
	}
	freeaddrinfo(result);
	return (ip);
}

bool Server::_initServers(void)
{
	std::vector<ServerConfig>			serverConfigs;
	std::vector<ServerConfig>::iterator	it;
	std::string							port;
	std::string							host;
	int									serverFd;

	serverConfigs = _configs.getServers();
	for (it = serverConfigs.begin(); it != serverConfigs.end(); it++)
	{
		host = (*it).getHost();
		port = (*it).getPort();
		if (_isServerAlreadyInitialized(host, port))
			continue ;
		serverFd = _getServerFd(host, port);
		if (serverFd == -1)
		{
			_errorStartServerPrint(host, port);
			return (false);
		}
		_addNewServerFd(serverFd);
		_addNewServerEndpoint(host, port);
	}
	return (true);
}

bool Server::_initEventLoop(void)
{
	_eventLoop.setMessenger(&_messenger);
	_eventLoop.registerEventHandler(new ReadSocketHandler(new HandleReq()));
	_eventLoop.registerEventHandler(new WriteHandler(new HandleRes(_configs)));
	_eventLoop.registerEventHandler(new ReadCgiHandler());
	_eventLoop.registerEventHandler(new WriteCgiHandler());
	_eventLoop.registerEventHandler(new TypeTransitionHandler());
	return (true);
}

bool Server::_initConnections(void)
{
	_connections.setMessenger(&_messenger);
	return (true);
}

bool Server::_initEventDemux(void)
{
	return (true);
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