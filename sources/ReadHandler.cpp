/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/22 11:55:24 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadHandler.hpp"

#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

ReadHandler::ReadHandler(void)
{
	//Default ReadHandler Constructor
}

ReadHandler::ReadHandler(const ReadHandler &src)
{
	//ReadHandler Copy Constructor
}

ReadHandler::~ReadHandler(void)
{
	//Default ReadHandler Destructor
}

/*
ReadHandler &ReadHandler::operator=(const ReadHandler &src)
{
	//ReadHandler Copy Assignment Operator
}
*/

void send_response_test(int socket_fd)
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

void ReadHandler::handleEvent(int event)
{
	char	buffer[30000];
	ssize_t	valread;

	for(int i = 0; i < 30000; i++)
		buffer[i] = 0;

	valread = read(event, buffer, 30000 - 1);
	send_response_test(event);
	std::cout << "handle READ event: " << event << std::endl;
}

EventType ReadHandler::getHandleType(void)
{
	return (READ_EVENT);
}
