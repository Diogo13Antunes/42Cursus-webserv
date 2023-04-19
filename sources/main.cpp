/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/04/17 15:17:42 by dsilveri         ###   ########.fr       */
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

#include <fstream>

// Test comminication wit sockets

// sockaddr_in -> especific IP-based communication
// sockaddr    -> is a generic descriptor for any kind of socket operation
// http://localhost:8080/

// server code

#define PORT 8080

int main(int ac, char **av)
{
	int server_fd, new_socket;
	long valread;
	struct sockaddr_in address;
	int addrlen;

	std::string head;
	std::string body;
	std::string res;
	
	if (ac != 2)
		return (write(2, "Error: Invalid number of Arguments!\n", strlen("Error: Invalid number of Arguments!\n")));

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		perror("cannot create socket");
		return 0; 
	}

	// este if seve para podermos usar sempre a mesma porta
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

	struct pollfd fds[10 + 1];
	int	nfds = 1;
	int timeout = 5000;

	fds[0].fd = server_fd;
	fds[0].events = POLLIN;

    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
		char buffer[30000] = {0};

        valread = read(new_socket , buffer, 30000);

		std::cout << "read: " << valread << std::endl;

		std::ifstream	htmlFile(av[1]);
		std::string		buff;

		while (std::getline(htmlFile, buff))
			body += buff;

		head += "HTTP/1.1 200 OK\r\nContent-length: ";
		head += body.size() + "\r\n";
		head += "Content-Type: text/html\r\n\r\n";

		res = head + body + "\r\n\r\n";

		//send(new_socket, "HTTP/1.1 200 OK\r\nContent-length: 5\r\n\r\nhello\r\n\r\n", 48, 0);
		send(new_socket, res.c_str(), res.size(), 0);
		std::cout << "buffer:\n" << buffer << std::endl;
        close(new_socket);
		res.clear();
		body.clear();
		head.clear();

		poll(fds, nfds, timeout);
		if (fds[0].revents & POLLIN)
			std::cout << "Hello from backend!\n";
		else
			std::cout << "GoodBye from backend!\n";
    }

	return (0);
}
