/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WriteHandler.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:02:47 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/29 16:47:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <sys/socket.h>

#include "WriteHandler.hpp"
#include "HandleRes.hpp"

WriteHandler::WriteHandler(void): IEventHandler()
{
	_handleRes = NULL;
}

WriteHandler::WriteHandler(HandleRes *handleRes): IEventHandler()
{
	_handleRes = handleRes;
}

/*
WriteHandler::WriteHandler(ConfigsData data):
	IEventHandler(),
	_data(data)
{}
*/

WriteHandler::WriteHandler(const WriteHandler &src) {}

WriteHandler::~WriteHandler(void) 
{
	if (_handleRes)
		delete _handleRes;
}

/*
WriteHandler &WriteHandler::operator=(const WriteHandler &src)
{
	//WriteHandler Copy Assignment Operator
}
*/

/*
void send_response_test(int socket_fd)
{
	std::string head;
	std::string body;
	std::string res;

	std::stringstream out;

	//body = "<html><head><title>WebServer</title></head><body><h1>Hello World</h1></body></html>\r\n\r\n";
	//body = "<html><head><title>WebServer</title></head><body><h1>Hello World</h1><img src=\"https://res.cloudinary.com/dk-find-out/image/upload/q_70,c_pad,w_1200,h_630,f_auto/MonolophosaurusHiRes_usl6ti.jpg\" alt=\"Dinosaur\" /></body></html>\r\n\r\n";
	body = "<html><head><title>WebServer</title></head><body><h1>Hello World</h1><img src=\"dinosaur.jpg\" alt=\"Dinosaur\" /></body></html>\r\n\r\n";
	out << body.size();
	
	head = "HTTP/1.1 200 OK\r\nContent-length: ";
	head += out.str();
	head += "\r\n";
	head += "Content-Type: text/html\r\n\r\n";
	res = head + body;
	send(socket_fd, res.c_str(), res.size(), 0);
}
*/

/*
void send_response_test(Event *event)
{
	std::string res;

	res = event->getResponse();
	send(event->getFd(), res.c_str(), res.size(), 0);
}
*/

void WriteHandler::handleEvent(Event *event)
{
	//HandleRes	handleRes(event);

	//std::cout << "handle WRITE event " << event->getFd() << std::endl;
	//event->createResponse(_data);

	_handleRes->setEvent(event);
	_handleRes->handle();
	

	// No final passar para o estado COMPLETE_EVENT
	//event->setState(COMPLETE_EVENT);

	//send_response_test(event);
}




EventType WriteHandler::getHandleType(void)
{
	return (WRITE_EVENT);
}
