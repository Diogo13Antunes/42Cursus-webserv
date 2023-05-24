/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/24 17:48:54 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

//#include <sys/poll.h>
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

/*

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

*/

void send_response_test1(int socket_fd)
{
	std::string head;
	std::string body;
	std::string res;

	std::stringstream out;

	body = "<html><head><title>WebServer</title></head><body><h1>Hello World</h1></body></html>\r\n\r\n";
	out << body.size();
	
	head = "HTTP/1.1 200 OK\r\nContent-length: ";
	head += out.str();
	head += "\r\n";
	head += "Content-Type: text/html\r\n\r\n";
	res = head + body;
	send(socket_fd, res.c_str(), res.size(), 0);
}


int main1(void)
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

    int epollFd = epoll_create1(0);
    if (epollFd == -1) {
        std::cerr << "Failed to create epoll instance." << std::endl;
        return 1;
    }

	epoll_event event;
    event.data.fd = server_fd;
    event.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
        std::cerr << "Failed to add server socket to epoll." << std::endl;
        return 1;
    }

	std::cout << "valor do epoll_fd " << epollFd << std::endl;

	int max_events = 1024;
	epoll_event events[max_events];
	int numEvents;

	char	buffer[30000];
	ssize_t	valread;
	int flags;

    while(1)
    {
		numEvents = epoll_wait(epollFd, events, max_events, -1);
		std::cout << "começa loop num: " << numEvents << std::endl;
		for (int i = 0; i < numEvents; i++) 
		{
			if (events[i].data.fd == server_fd)
			{
				std::cout << "addiciona evento a lista" << std::endl;
				if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
				{
					perror("In accept");
					exit(EXIT_FAILURE);
				}
				event.data.fd = new_socket;
                event.events = EPOLLIN | EPOLLET;
				// Set client socket to non-blocking mode
            	flags = fcntl(new_socket, F_GETFL, 0);
                fcntl(new_socket, F_SETFL, flags | O_NONBLOCK);
                epoll_ctl(epollFd, EPOLL_CTL_ADD, new_socket, &event); // has to verify error returned
			}
			else 
			{
				std::cout << "verifica o evento mesmo" << std::endl;
				if (events[i].events & EPOLLIN)
				{
						for(int i = 0; i < 30000; i++)
							buffer[i] = 0;
						valread = read(events[i].data.fd, buffer, 30000 - 1);
						//std::cout << buffer << std::endl;
						send_response_test1(events[i].data.fd);
				}
			}
		}
	}
	return (0);
}


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
	EventLoop			eventLoop(&messenger);
	Connections			conns(&messenger);

	eventLoop.registerEvent(factory.getEventHandler(READ_EVENT));
	eventLoop.registerEvent(factory.getEventHandler(WRITE_EVENT));

	EventDemux eventDemux(server_fd, address, (socklen_t) addrlen);
	eventDemux.setMessenger(&messenger);

	messenger.registerModule(&conns);
	messenger.registerModule(&eventLoop);
	messenger.registerModule(&eventDemux);

    while(1)
    {
		conns.updateAllConnections();
		eventDemux.waitAndDispatchEvents();
	}

	return (0);
}

