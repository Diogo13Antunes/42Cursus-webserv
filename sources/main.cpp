/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/11 12:36:15 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/poll.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <sys/epoll.h>
#include <sstream>
#include <ctime>
#include <fcntl.h>

#include "Connection.hpp"
#include "Connections.hpp"

#include "EventLoop.hpp"
#include "Messenger.hpp"

#include "EventDemux.hpp"

#define PORT 8080

#include "Configs.hpp"
#include "ConfigsData.hpp"
#include "RequestParser.hpp"
#include "RequestData.hpp"

#include "Timer.hpp"

#include "Server.hpp"

bool	initConfigs(const char *filename, ConfigsData &data)
{
	try
	{
		Configs	cfg(filename);
		data.setupConfigs(cfg.getFileContentVector());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (false);
	}
	return (true);
}


int main(int argc, char **argv)
{
	ConfigsData	confData;

	if (argc != 2)
	{
		std::cout << "Error: No config file" << std::endl;
		return (0);
	}
	if (!initConfigs(argv[1], confData))
		return (-1);
	Server server(confData);
	if (server.init())
		server.start();
	return (0);
}

/*
int main1(int argc, char **argv)
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen;

	if (argc != 2)
	{
		std::cout << "Error: No config file" << std::endl;
		return (0);
	}

	
	// cria socket
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("cannot create socket");
		return 0; 
	}

	// para desimpedir o porto
	int enable = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		close(server_fd);
		return (EXIT_FAILURE);
	}


	memset((char *)&address, 0, sizeof(address)); 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = htonl(INADDR_ANY); 
	address.sin_port = htons(PORT);
	addrlen = sizeof(address);
	
	if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) 
	{
    	perror("bind failed"); 
    	return 0; 
	}
    if (listen(server_fd, 100) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

	ConfigsData	confData;
	if (!initConfigs(argv[1], confData))
		return (1);

	Messenger			messenger;

	EventLoop			eventLoop;
	Connections			conns;
	EventDemux			eventDemux(server_fd, address, (socklen_t) addrlen);

	eventLoop.setMessenger(&messenger);
	conns.setMessenger(&messenger);
	eventDemux.setMessenger(&messenger);
	
	//eventLoop.registerEventHandler(factory.getEventHandler(READ_EVENT));
	eventLoop.registerEventHandler(new ReadSocketHandler(new HandleReq()));
	eventLoop.registerEventHandler(new WriteHandler(new HandleRes(confData)));
	//eventLoop.registerEventHandler(new CGIHandler(new HandleCgi()));
	eventLoop.registerEventHandler(new ReadCgiHandler());
	eventLoop.registerEventHandler(new WriteCgiHandler());
	eventLoop.registerEventHandler(new TypeTransitionHandler());
	//eventLoop.registerEventHandler(factory.getEventHandler(WRITE_EVENT));

	//std::cout << "Server started at port: " << PORT << std::endl;
    while(1)
    {
		conns.updateAllConnections();
		eventDemux.waitAndDispatchEvents();
		eventLoop.handleEvents();
	}
	return (0);
}
*/
