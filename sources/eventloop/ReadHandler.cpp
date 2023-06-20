/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/20 17:10:44 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadHandler.hpp"

#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <string>


/*
static std::string createResponse(std::string path, std::string contentType);
static std::string getFileContent(std::string fileName);
static std::string createResponsePageNotFound(void);
static std::string getFileType(std::string path);
*/

ReadHandler::ReadHandler(void) {}

ReadHandler::ReadHandler(ConfigsData data):
	IEventHandler(),
	_data(data)
{}

ReadHandler::ReadHandler(const ReadHandler &src) {}

ReadHandler::~ReadHandler(void) {}

/*
ReadHandler &ReadHandler::operator=(const ReadHandler &src)
{
	//ReadHandler Copy Assignment Operator
}
*/

/*
void ReadHandler::handleEvent(Event *event)
{
	char	buffer[90000];
	ssize_t	valread;

	for(int i = 0; i < 90000; i++)
		buffer[i] = 0;


	valread = read(event->getFd(), buffer, 90000 - 1);

	std::cout << buffer << std::endl;
	std::cout << "handle READ event: " << event->getFd() << std::endl;
}
*/

/*
GET /echo HTTP/1.1
Host: reqbin.com
Accept: text/html
Connection: keep-alive
*/


// estes dados tem de ser guardados no meu evento
// usar um estado para indicar se parse request line, header, or body
// Estado 0 - estado inicial request line (troca para estado 1) \r\n
// Estado 1 - parse do header (troca para estado 2 após \r\n\r\n e content-length)
// Estado 2 - parse Body (leitura do content-length)

/*
GET /echo HTTP/1.1 - resquest Line
Host: reqbin.com - header parser

// pedido 1
GET /echo HTTP/1.1
Host: reqbin.com
Accept: tex

//pedido 2
t/html
Connection: keep-alive\r\n\r\n

Accept: tex
t/html

Accept: text/html

Accept: text/html\r\n
*/

/*
void ReadHandler::handleEvent(Event *event)
{

	char	buffer[90000];
	ssize_t	valread;

	for(int i = 0; i < 90000; i++)
		buffer[i] = 0;
	valread = read(event->getFd(), buffer, 90000 - 1);

	RequestData											req;
	RequestParser										request1(event->getFd());
	std::string											requestLine;
	std::map<std::string, std::vector<std::string> >	requestHeader;
	std::string											requestBody;
	std::string											filePath;
	std::string											reqPath;
	std::string											contentType;

	requestLine = request1.getRequestLine();
	requestHeader = request1.getRequestHeader();
	requestBody = request1.getRequestBody();

	req.setRequestLine(requestLine);
	req.setRequestHeader(requestHeader);
	req.setRequestBody(requestBody);

	reqPath = req.getPath();
	std::cout << "path: " << reqPath << std::endl;


	if (!reqPath.compare("/"))
		filePath = _data.getConfig("root");
	else
		filePath = _data.getConfig(req.getPath());


	if (filePath.size())//existe rota
		event->setResponse(createResponse(filePath, "text/html"));
	else
	{
		reqPath = _data.getConfig("path") + "/" + reqPath;
		contentType = _data.getConfig(getFileType(reqPath));
		event->setResponse(createResponse(reqPath, contentType));
	}
}
*/

void ReadHandler::handleEvent(Event *event)
{
	char			buffer[2];
	ssize_t			valread;
	RequestParser	parser;
	short			state;

	for(int i = 0; i < 2; i++)
		buffer[i] = 0;
	valread = read(event->getFd(), buffer, 2 - 1);

	//std::cout << buffer << std::endl;

	//event->updateReqRaw(buffer);
	//std::cout << "---------------------" << std::endl;
	//std::cout << event->getReqRaw() << std::endl;

	state = event->getParseState();
	if (state == HEADER_HANDLE || state == BODY_HANDLE)
	{
		event->updateReqRaw(buffer);
		state = event->getParseState();
	}
	if (state == HEADER_DONE)
	{
		std::string str = event->getHeaderRaw();
		parser.headerParse(str);
		event->setResquestHeader(parser.getRequestLine(), parser.getRequestHeader());

		//std::cout << "body size: " << event->getBodySize() << std::endl;
		if (event->getBodySize())
			event->setParseState(BODY_HANDLE);
	}
	if (state == BODY_DONE)
	{
		std::string str = event->getReqRaw();
		parser.bodyParse(str);
		event->setResquestBody(parser.getRequestBody());

		
	}
	if (state == BODY_DONE || (state == HEADER_DONE && !event->getBodySize()))
	{
		event->createResponse(_data);
		event->setState(WRITE_EVENT);
	}

	// saber se existe body -> content-leng
	// Depois estar terminado verificar se existe content leng -> criar no evento um field com bodySize


}

EventType ReadHandler::getHandleType(void)
{
	return (READ_EVENT);
}

/*
static std::string createResponse(std::string path, std::string contentType)
{
	std::string response;
	std::string body;
	std::stringstream bodySize;

	body = getFileContent(path);
	if (body.empty())
		return (createResponsePageNotFound());

	// get content type str

	bodySize << body.size();
	response = "HTTP/1.1 200 OK\r\nContent-length: ";
	response += bodySize.str();
	response += "\r\n";
	response += "Content-Type: " + contentType;
	response += "\r\n\r\n";
	response += body;
	return (response);
}

static std::string getFileContent(std::string fileName)
{
	std::ifstream	file(fileName.c_str());
	std::string		buff;
	std::string		body;

	if (file.is_open())
	{
		while (std::getline(file, buff))
		{
			body += buff + "\n";
		}
		file.close();
	}
	else
		std::cout << "Error: can't open file" << std::endl;
	return (body);
}

static std::string createResponsePageNotFound(void)
{
	std::string response;
	std::string body;
	std::stringstream bodySize;

	body = "<html><head></head><body><h1>404 - Page not Found</h1><a href=\"/\">pagina inicial</a></body></html>";

	bodySize << body.size();
	response = "HTTP/1.1 404 KO\r\nContent-length: ";
	response += bodySize.str();
	response += "\r\n";
	response += "Content-Type: text/html\r\n\r\n";
	response += body;

	return (response);
}

static std::string getFileType(std::string path)
{
	std::string type;
	size_t		dotIdx;

	dotIdx = (path.find_last_of('.')) + 1;
	if (dotIdx < path.size())
		type = path.substr(dotIdx, path.size());
	return (type);
}
*/