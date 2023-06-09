/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReadHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/09 16:52:56 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReadHandler.hpp"

#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <string>


static std::string createResponse(std::string path, std::string contentType);
static std::string getFileContent(std::string fileName);
static std::string createResponsePageNotFound(void);
static std::string getFileType(std::string path);

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

void ReadHandler::handleEvent(Event *event)
{

	/*char	buffer[90000];
	ssize_t	valread;

	for(int i = 0; i < 90000; i++)
		buffer[i] = 0;
	valread = read(event->getFd(), buffer, 90000 - 1);*/

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

EventType ReadHandler::getHandleType(void)
{
	return (READ_EVENT);
}

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