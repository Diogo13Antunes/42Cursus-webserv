/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/03 12:43:59 by dsilveri         ###   ########.fr       */
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

	struct pollfd fds[10];
	
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

	int counter = 0; 

    while(1)
    {
		std::cout << "Wait new connection" << std::endl;

		poll(fds, 10, 1000);

		

		if (fds[0].revents && POLLIN)
		{
			if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
			{
				perror("In accept");
				exit(EXIT_FAILURE);
			}
			valread = read(new_socket , buffer, 30000);
			std::cout << "###########################" << std::endl;
			std::cout << buffer << std::endl;

			send_response(new_socket);		
		}

    }
	return (0);
}

void send_response(int socket_fd)
{
	std::string head;
	std::string body;
	std::string res;

	body += "<html><head><title>WebServer</title></head><body><h1>Hello World</h1></body></html>";
	head += "HTTP/1.1 200 OK\r\nContent-length: ";
	head += "85\r\n";
	head += "Content-Type: text/html\r\n\r\n";
	res = head + body + "\r\n\r\n";

	send(socket_fd, res.c_str(), res.size(), 0);
	//write(socket_fd, res.c_str(), res.size());

	std::cout << "I am block on close" << std::endl;
    if (close(socket_fd) == -1)
		std::cout << "Erro a fechar" << std::endl;

	std::cout << "close ends" << std::endl;
}
