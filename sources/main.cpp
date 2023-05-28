/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/28 14:29:24 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

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


// Test comminication wit sockets

// sockaddr_in -> especific IP-based communication
// sockaddr    -> is a generic descriptor for any kind of socket operation
// http://localhost:8080/

// server code

int main(void)
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen;

	
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

	Messenger			messenger;
	EventHandlerFactory	factory;

	EventLoop			eventLoop;
	Connections			conns;
	EventDemux			eventDemux(server_fd, address, (socklen_t) addrlen);

	eventLoop.setMessenger(&messenger);
	conns.setMessenger(&messenger);
	eventDemux.setMessenger(&messenger);

	
	eventLoop.registerEvent(factory.getEventHandler(READ_EVENT));
	eventLoop.registerEvent(factory.getEventHandler(WRITE_EVENT));

    while(1)
    {
		conns.updateAllConnections();
		eventDemux.waitAndDispatchEvents();
		eventLoop.handleEvents();
	}
	
	return (0);
}

