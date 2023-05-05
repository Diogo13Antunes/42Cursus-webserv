/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/05 17:44:58 by dsilveri         ###   ########.fr       */
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

#include "Connection.hpp"
#include "Connections.hpp"


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

	Connections conns;
	
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

    while(1)
    {
		//std::cout << "Wait new connection" << std::endl;

		res_poll = poll(fds, n_events, 10000);


		std::cout << "res_poll: " << res_poll << std::endl;

		//if (res_poll > 0 && fds[0].revents && POLLIN)
		if (fds[0].revents && POLLIN)
		{		
			if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
			{
				perror("In accept");
				exit(EXIT_FAILURE);
			}
			conns.addConnection(new_socket, POLLIN);
			conns.showConnections();



			valread = read(new_socket , buffer, 30000);
			std::cout << "index: 0" << std::endl;
			std::cout << buffer << std::endl;
			send_response(new_socket);

			if (aux == 0)
			{
				aux = 1;
				fds[1].fd = new_socket;
				fds[1].events = POLLIN;
				fds[1].revents = 0;
				n_events++;
			}
			else if (aux == 1)
			{
				aux = 2;
				fds[2].fd = new_socket;
				fds[2].events = POLLIN;
				fds[2].revents = 0;
				n_events++;
			}

			fds[0].revents = 0;
		}
		//else if (res_poll > 0 && fds[1].revents && POLLIN)
		else if (fds[1].revents && POLLIN)
		{
			valread = read(fds[1].fd , buffer, 30000);
			send_response(fds[1].fd);
			std::cout << "index: 1" << std::endl;
			std::cout << buffer << std::endl;
			fds[1].revents = 0;
		}
		//else if (res_poll > 0 && fds[2].revents && POLLIN)
		else if (fds[2].revents && POLLIN)
		{
			valread = read(fds[2].fd , buffer, 30000);
			send_response(fds[2].fd);
			std::cout << "index: 2" << std::endl;
			std::cout << buffer << std::endl;
			fds[2].revents = 0;
		}
    }
	return (0);
}

void send_response(int socket_fd)
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
	//res = head + body + "\r\n\r\n";
	res = head + body;

	std::cout << "#################" << std::endl; 
	std::cout << head << std::endl; 

	send(socket_fd, res.c_str(), res.size(), 0);
	//write(socket_fd, res.c_str(), res.size());

    //if (close(socket_fd) == -1)
	//	std::cout << "Erro a fechar" << std::endl;
}


/*
int main(void)
{

	Connections c;

	c.addConnection(new Connection(22, 0));
	c.addConnection(new Connection(33, 0));
	c.addConnection(new Connection(44, 0));
	c.showConnections();
	
	return (0);
}
*/