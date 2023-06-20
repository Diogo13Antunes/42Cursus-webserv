/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:31 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/20 14:20:05 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"

static std::string createResponse1(std::string path, std::string contentType);
static std::string getFileContent(std::string fileName);
static std::string createResponsePageNotFound(void);
static std::string getFileType(std::string path);

Event::Event(void) {}

Event::Event(int fd, int state):
	_fd(fd),
	_state(state),
	_parseState(NONE)
{}

Event::Event(const Event &src) {}

Event::~Event(void) {}

/*
Event &Event::operator=(const Event &src)
{
	//Event Copy Assignment Operator
}
*/

int Event::getFd(void)
{
	return (_fd);
}

short Event::getState(void)
{
	return (_state);
}

std::string	Event::getResponse(void)
{
	return (_res);
}

std::string Event::getReqRaw(void)
{
	return (_reqRaw);
}

std::string Event::getHeaderRaw(void)
{
	return (_headerRaw);
}

short Event::getParseState(void)
{
	return (_parseState);
}

void Event::setState(short state)
{
	_state = state;
}

void Event::setResponse(std::string res)
{
	_res = res;
}

void Event::setResquestHeader(std::string reqLine, std::map<std::string, std::vector<std::string> > reqHeader)
{
	_reqParsed.setRequestLine(reqLine);
	_reqParsed.setRequestHeader(reqHeader);
}

void Event::updateReqRaw(std::string req)
{
	size_t	headerSize;

	_reqRaw += req;

	headerSize = _reqRaw.find("\r\n\r\n");
	if (headerSize != std::string::npos)
	{
		_parseState = HEADER_DONE;
		_headerRaw = _reqRaw.substr(0, headerSize + 4);
		_reqRaw = _reqRaw.substr(headerSize + 4);
		std::cout << "HEADER DONE" << std::endl;

		std::cout << "HEADER RAW" << std::endl;
		std::cout << _headerRaw << std::endl;
		std::cout << "Request RAW" << std::endl;
		std::cout << _reqRaw << std::endl;
	}
}

void Event::createResponse(ConfigsData configsData)
{
	std::string	reqPath;
	std::string filePath;
	std::string	contentType;

	reqPath = _reqParsed.getPath();
	std::cout << "path: " << reqPath << std::endl;

	if (!reqPath.compare("/"))
		filePath = configsData.getConfig("root");
	else
		filePath = configsData.getConfig(reqPath);

	if (filePath.size())//existe rota
		this->setResponse(createResponse1(filePath, "text/html"));
	else
	{
		reqPath = configsData.getConfig("path") + "/" + reqPath;
		contentType = configsData.getConfig(getFileType(reqPath));
		this->setResponse(createResponse1(reqPath, contentType));
	}

	std::cout << "respose: " << this->getResponse() << std::endl;
}

static std::string createResponse1(std::string path, std::string contentType)
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
