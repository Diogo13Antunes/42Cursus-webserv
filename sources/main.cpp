/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/20 12:27:22 by dsilveri         ###   ########.fr       */
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

/* int main(int ac, char **av)
{
	ConfigsData	data;

	if (ac != 2)
	{
		Terminal::printErrors("Invalid number of Arguments");
		return (1);
	}

	if (!initConfigs(av[1], data))
		return (1);

	return (0);
} */

int main1(int ac, char **av)
{
	int	fd1;
	RequestData	data;

	if (ac < 2)
	{
		Terminal::printErrors("Invalid number of Arguments");
		return (1);
	}

	fd1 = open(av[1], O_RDONLY);
	if (fd1 < 0)
	{
		Terminal::printErrors("Invalid Request File");
		return (1);
	}

	try
	{
		/*RequestParser 										request1(fd1);
		std::string											requestLine;
		std::map<std::string, std::vector<std::string> >	requestHeader;
		std::string											requestBody;

		requestLine = request1.getRequestLine();
		requestHeader = request1.getRequestHeader();
		requestBody = request1.getRequestBody();

		// std::cout << "Line: " << requestLine << std::endl;

		// std::cout << "[KEY] | [VALUE]" << std::endl;
		// std::map<std::string, std::vector<std::string> >::iterator	it;
		// std::vector<std::string>									elements;
		// for (it = requestHeader.begin(); it != requestHeader.end(); it++)
		// {
			// elements = (*it).second;
			// std::cout << "[" << (*it).first << "] | ";
			// for (size_t i = 0; i < elements.size(); i++)
			// {
				// std::cout << "[" << elements.at(i).c_str() << "]";
				// if (i < elements.size() - 1)
					// std::cout << " , ";
			// }
			// std::cout << std::endl;
		// }

		// std::cout << "-------------------- BODY --------------------" << std::endl;
		// std::cout << requestBody;
		// std::cout << "----------------------------------------------" << std::endl;

		data.setRequestLine(requestLine);
		data.setRequestHeader(requestHeader);
		data.setRequestBody(requestBody);*/
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (1);
	}

	std::vector<std::string>							line;
	std::map<std::string, std::vector<std::string> >	header;
	std::string											body;

	line = data.getRequestLine();
	header = data.getRequestHeader();
	body = data.getRequestBody();


	std::cout << "---------- LINE ----------" << std::endl;
	for (size_t i = 0; i < line.size(); i++)
		std::cout << "\'" << line.at(i).c_str() << "\'" << std::endl; 
	std::cout << "--------------------------" << std::endl;

	std::cout << "-------------------- HEADER --------------------" << std::endl;
	std::cout << "[KEY] | [VALUE]" << std::endl;
	std::map<std::string, std::vector<std::string> >::iterator	it;
	std::vector<std::string>									elements;
	for (it = header.begin(); it != header.end(); it++)
	{
		elements = (*it).second;
		std::cout << "[" << (*it).first << "] | ";
		for (size_t i = 0; i < elements.size(); i++)
		{
			std::cout << "[" << elements.at(i).c_str() << "]";
			if (i < elements.size() - 1)
				std::cout << " , ";
		}
		std::cout << std::endl;
	}
	std::cout << "------------------------------------------------" << std::endl;

	std::cout << "-------------------- BODY --------------------" << std::endl;
	std::cout << body;
	std::cout << "----------------------------------------------" << std::endl;

	return (0);
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
	eventLoop.registerEventHandler(new ReadHandler(data));
	eventLoop.registerEventHandler(factory.getEventHandler(WRITE_EVENT));
	
    while(1)
    {
		conns.updateAllConnections();
		eventDemux.waitAndDispatchEvents();
		eventLoop.handleEvents();
	}
	return (0);
}
