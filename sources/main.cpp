/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/23 10:24:27 by dsilveri         ###   ########.fr       */
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

#include <sstream>

#include <ctime>

#include "Connection.hpp"
#include "Connections.hpp"

#include "EventLoop.hpp"
#include "EventHandlerFactory.hpp"

#include "Messenger.hpp"



// Test comminication wit sockets

// sockaddr_in -> especific IP-based communication
// sockaddr    -> is a generic descriptor for any kind of socket operation
// http://localhost:8080/

// server code

#define PORT 8080

void send_response(int socket_fd);


int main(void)
{
	int server_fd, new_socket;
	long valread;
	struct sockaddr_in address;
	int addrlen;

	int res_poll = 0;
	int n_events = 1;

	int aux = 0;

	int a = POLLPRI;

	struct pollfd fds[3];

	Messenger messenger;
	Connections conns(&messenger);

	struct pollfd serverConn;

	
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
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

	char buffer[30000] = {0};


	fds[0].fd = server_fd;
	fds[0].events = POLLIN;
	fds[0].revents = 0;

	conns.addNewConnection(new Connection(server_fd, POLLIN, 0));

	struct pollfd *				_fds;

	
	_fds = new struct pollfd[1];

	_fds[0].fd = 3;
	_fds[0].events = POLLIN;
	
	struct pollfd *fds1;
	int fdsSize;

	Event *event;

	
	EventLoop			eventLoop(&messenger);
	EventHandlerFactory	factory;

	eventLoop.registerEvent(factory.getEventHandler(READ_EVENT));
	eventLoop.registerEvent(factory.getEventHandler(WRITE_EVENT));

	messenger.registerModule(&conns);
	messenger.registerModule(&eventLoop);

    while(1)
    {
		conns.removeExpiredConnections();
		fds1 = conns.getPollFds();
		fdsSize = conns.getNumOfConnections();

		res_poll = poll(fds1, fdsSize, 1000);

		if (res_poll > 0)
		{
			serverConn = conns.getServerConnection();
			if (serverConn.revents == POLLIN)
			{
				if ((new_socket = accept(serverConn.fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
				{
					perror("In accept");
					exit(EXIT_FAILURE);
				}
				conns.addNewConnection(new Connection(new_socket, serverConn.events, serverConn.revents));
			}
			conns.updateConnections();
		}
		eventLoop.handleEvents();
	}
	
	return (0);
}


/*
int main(void)
{
	EventLoop			eventLoop;
	EventHandlerFactory	factory;

	eventLoop.registerEvent(factory.getEventHandler(READ_EVENT));
	eventLoop.registerEvent(factory.getEventHandler(WRITE_EVENT));
	eventLoop.handleEvents();

	return (0);
}
*/