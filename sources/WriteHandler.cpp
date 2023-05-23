/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:47 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/23 10:31:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <sys/socket.h>

#include "WriteHandler.hpp"

WriteHandler::WriteHandler(void)
{
	//Default WriteHandler Constructor
}

WriteHandler::WriteHandler(const WriteHandler &src)
{
	//WriteHandler Copy Constructor
}

WriteHandler::~WriteHandler(void)
{
	//Default WriteHandler Destructor
}

/*
WriteHandler &WriteHandler::operator=(const WriteHandler &src)
{
	//WriteHandler Copy Assignment Operator
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

void WriteHandler::handleEvent(Event *event)
{
	std::cout << "handle WRITE event " << event->getFd() << std::endl;

	send_response_test(event->getFd());
}

EventType WriteHandler::getHandleType(void)
{
	return (WRITE_EVENT);
}
