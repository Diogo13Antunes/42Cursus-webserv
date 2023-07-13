/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:31 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/13 15:44:54 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"

#include "Timer.hpp"

static std::string createResponse1(std::string path, std::string contentType);
static std::string getFileContent(std::string fileName);
static std::string createResponsePageNotFound(void);
static std::string getFileType(std::string path);

Event::Event(void) {}

Event::Event(int fd, int state):
	_fd(fd),
	_state(state),
	_parseState(HEADER_HANDLE),
	_reqState(HEADER_PROCESS),
	_resState(0),
	_numWrited(0),
	_idx(0),
	_bytesReadBody(0),
	_totalBytesSend(0),
	_resState1(CREATE_HEADER),
	_errorCode(0),
	_cgiFlag(false),
	_cgiState(EXEC_CGI),
	_timeoutSec(120),
	_creationTime(Timer::getActualTimeStamp()),
	_clientClosed(false),
	_cgiEx(NULL)
{}

Event::Event(const Event &src) {}

Event::~Event(void)
{
	if (_cgiEx)
		delete _cgiEx;
}

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

std::string&	Event::getResponse(void)
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

size_t Event::getBodySize(void)
{
	return (_reqParsed.getContentLenght());
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

void Event::setResquestBody(std::string body)
{
	_reqParsed.setRequestBody(body);
}

void Event::setParseState(int state)
{
	_parseState = state;
}

void Event::updateReqRaw(std::string req)
{
	size_t	headerSize;
	size_t	bodySize = 0;
	size_t	currentBodySize = 0;

	_reqRaw += req;

	if (_parseState == HEADER_HANDLE)
	{
		headerSize = _reqRaw.find("\r\n\r\n");
		if (headerSize != std::string::npos)
		{
			setParseState(HEADER_DONE);
			_headerRaw = _reqRaw.substr(0, headerSize + 4);
			_reqRaw = _reqRaw.substr(headerSize + 4);
		}
	}
	else if (_parseState == BODY_HANDLE)
	{
		if (_reqRaw.size() == this->getBodySize())
			setParseState(BODY_DONE);
	}

	//this->setBodySize();
}

// Para remover mais tarde
bool Event::isBodyComplete(void)
{
	bool bodyComplete;

	bodyComplete = false;
	if (_reqRaw.size() == this->getBodySize())
		bodyComplete = true;
	return (bodyComplete);
}

void Event::createResponse(ConfigsData configsData)
{
	std::string	reqPath;
	std::string filePath;
	std::string	contentType;

	reqPath = _reqParsed.getPath();
	//std::cout << "path: " << reqPath << std::endl;

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

	//std::cout << "respose: " << this->getResponse() << std::endl;
}


// New Methods
StateType Event::getReqState(void)
{
	return (_reqState);
}

void Event::setReqState(StateType reqState)
{
	_reqState = reqState;
}


void Event::updateReqRaw1(std::string req)
{
	_reqRaw += req;
}

void Event::setReqRaw1(std::string req)
{
	_reqRaw = req;
}

const std::string&  Event::getReqRaw1(void)
{
	return (_reqRaw);
}

void Event::setHeaderRaw(std::string header)
{
	_headerRaw = header;
}

void Event::setBodyRaw(std::string body)
{
	_bodyRaw = body;
}

std::string Event::getHeaderRaw1(void)
{
	return (_headerRaw);
}

std::string Event::getBodyRaw(void)
{
	return (_bodyRaw);
}

void Event::setResState(int resState)
{
	_resState = resState;
}

int Event::getResState(void)
{
	return (_resState);
}

void Event::setResVect(void)
{
	int maxSize;
	int copyed;
	int aux;

	//maxSize = 2000000;
	maxSize = 100000;
	copyed = 0;
	aux = 0;

	while (true)
	{
		aux = _res.size() - copyed;

		if (aux > maxSize)
		{
			_resVect.push_back(_res.substr(copyed, maxSize));
			copyed += maxSize;
		}
		else
		{
			_resVect.push_back(_res.substr(copyed, aux));
			copyed += aux;
		}
		if (copyed == _res.size())
			break;
	}
}

void Event::printVectDebug(void)
{
	std::cout << "############## Print Response ################" << std::endl;
	for (int i = 0; i < _resVect.size(); i++)
	{
		std::cout << _resVect.at(i) << std::endl;
	}
}

ssize_t Event::getNumWrited(void)
{
	return (_numWrited);
}

void Event::updateNumWrited(ssize_t numWrited)
{
	_numWrited += numWrited;
}


std::string& Event::getNextRes(void)
{
	//if (_resVect[_idx].empty() && _idx < _resVect.size() - 1)
	//	_idx++;

	//std::cout << "idx: " << _idx << std::endl;
	//std::cout << "vec size: " << _resVect.size() << std::endl;

	if (_idx >= _resVect.size())
		return (_resVect[_resVect.size() - 1]);
	return (_resVect[_idx]);
}

void Event::updateRes1(std::string res)
{
	if (_idx < _resVect.size())
		_resVect[_idx] = res;
}

void Event::updateIdx(void)
{
	//if (_idx < _resVect.size() - 1)
	//{
		_idx++;
	//}
}

bool Event::lastIdx(void)
{
	if (_idx >= _resVect.size())
	{
		return (true);
	}
	return (false);
}


std::string Event::getReqPath(void)
{
	return (_reqParsed.getPath());
}

// Static functions
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


// Functions for Handle Response
std::string Event::getFileName(void)
{
	return (_fileName);
}

void Event::setFileName(std::string fileName)
{
	_fileName = fileName;
}

size_t Event::getBytesReadBody(void)
{
	return (_bytesReadBody);
}

void Event::setBytesReadBody(size_t bytesReadBody)
{
	_bytesReadBody = bytesReadBody;
}

void Event::updateBytesReadBody(size_t bytesReadBody)
{
	_bytesReadBody += bytesReadBody;
}

size_t Event::getBodySize1(void)
{
	return (_bodySize);
}

void Event::setBodySize1(size_t bodySize)
{
	_bodySize = bodySize;
}

const std::string& Event::getRes(void)
{
	return (_res);
}

void Event::setRes(std::string res)
{
	_res = res;
}

void Event::updateRes(std::string res)
{
	_res += res;
}

size_t Event::getResSize(void)
{
	return (_resSize);
}

void Event::setResSize(size_t resSize)
{
	_resSize = resSize;
}

size_t Event::getTotalBytesSend(void)
{
	return (_totalBytesSend);
}

void Event::setTotalBytesSend(size_t totalBytesSend)
{
	_totalBytesSend = totalBytesSend;
}

void Event::updateTotalBytesSend(size_t totalBytesSend)
{
	_totalBytesSend += totalBytesSend;
}

StateResType Event::getResState1(void)
{
	return (_resState1);
}

void Event::setResState1(StateResType resState)
{
	_resState1 = resState;
}

int Event::getErrorCode(void)
{
	return (_errorCode);
}

void Event::setErrorCode(int errorCode)
{
	_errorCode = errorCode;
}

bool Event::getCgiFlag(void)
{
	return (_cgiFlag);
}

void Event::setCgiFlag(bool cgiFlag)
{
	_cgiFlag = cgiFlag;
}
bool Event::isEventTimeout(void)
{
	//std::cout << "EVENT TIME OUT" << std::endl;
	//return (Timer::isTimeoutExpired(_creationTime, _timeoutSec));
	return (false);
}

bool Event::isConnectionClose(void)
{
	std::vector<std::string> value;
	// Lower case or Upper Case ?

	value = _reqParsed.getHeaderValue("connection");

	if (!value.empty() && !value[0].compare("close"))
		return (true);
	return (false);
}

bool Event::isClientClosed(void)
{
	return (_clientClosed);
}

void Event::setClientClosed(void)
{
	_clientClosed = true;
}

// CGI Functions
CGIExecuter* Event::getCgiEx(void)
{
	return (_cgiEx);
}

void Event::setCgiEx(CGIExecuter *cgiEx)
{
	_cgiEx = cgiEx;
}

int Event::getCgiFd(void)
{
	if (_cgiEx)
		return (_cgiEx->getReadFD());
	return (-1);
}

StateCgiType	Event::getCgiState(void)
{
	return (_cgiState);
}

void	Event::setCgiState(StateCgiType state)
{
	_cgiState = state;
}

std::string		Event::getCgiScriptResult(void)
{
	return (_cgiScriptResult);
}

void	Event::updateCgiScriptResult(std::string src)
{
	_cgiScriptResult += src;
}
