/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/08 14:27:36 by dsilveri         ###   ########.fr       */
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
#include "EventHandlerFactory.hpp"

#include "Messenger.hpp"

#include "EventDemux.hpp"

#define PORT 8080

#include "Configs.hpp"
#include "ConfigsData.hpp"
#include "RequestParser.hpp"
#include "RequestData.hpp"

#include "Timer.hpp"

// O configs pode receber o data e modificar o data dentro dele.
bool	initConfigs(const char *filename, ConfigsData &data)
{
	std::string	key, value;

	try
	{
		Configs	cfg(filename);
		while (cfg.getNextConfig(key, value))
			data.addNewConfigs(key, value);
		//std::cout << "listen:   " << data.getListen() << std::endl;
		//std::cout << "ServName: " << data.getServerName() << std::endl;
		//std::cout << "Root:     " << data.getRoot() << std::endl;
		// std::cout << "Index:    " << data.getIndex() << std::endl;
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

	ConfigsData	data;
	initConfigs(argv[1], data);


	Messenger			messenger;
	EventHandlerFactory	factory;

	EventLoop			eventLoop;
	Connections			conns;
	EventDemux			eventDemux(server_fd, address, (socklen_t) addrlen);

	eventLoop.setMessenger(&messenger);
	conns.setMessenger(&messenger);
	eventDemux.setMessenger(&messenger);
	
	//eventLoop.registerEventHandler(factory.getEventHandler(READ_EVENT));
	eventLoop.registerEventHandler(new ReadHandler(new HandleReq()));
	eventLoop.registerEventHandler(new WriteHandler(new HandleRes(data)));
	eventLoop.registerEventHandler(new CGIHandler());
	//eventLoop.registerEventHandler(factory.getEventHandler(WRITE_EVENT));
	
	std::cout << "Server started at port: " << PORT << std::endl;
    while(1)
    {
		conns.updateAllConnections();
		eventDemux.waitAndDispatchEvents();
		eventLoop.handleEvents();
	}
	return (0);
}