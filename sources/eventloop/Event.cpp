/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:31 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/13 13:00:51 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Event.hpp"
#include "Timer.hpp"
#include "EventType.hpp"

#define TIMEOUT_SEC				200
#define CONNECTION_CLOSED		1
#define CONNECTION_KEEPALIVE	0

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
	_resState1(INITIAL_STATE),
	_errorCode(0),
	_cgiFlag(false),
	_timeoutSec(TIMEOUT_SEC),
	_creationTime(Timer::getActualTimeStamp()),
	_clientClosed(false),
	_cgiEx(NULL),
	_actualState(READ_SOCKET),
	_finished(false),
	_connectionClosed(-1),
	_clientDisconnect(false),
	//_cgiExitStatus(NO_EXIT_STATUS),
	_cgiSentChars(0),
	_statusCode(0),
	_redirectCode(0),
	_fileSize(0),
	_fileNumBytesRead(0),
	_serverConf(NULL),
	_numBytesSendCgi(0),
	_cgiWriteFd(-1),
	_cgiReadFd(-1),
	_cgiPid(0),
	_cgiExitStatus(0),
	_cgiScriptEndend(false),
	_cgiWriteFdClosed(false),
	_cgiReadFdClosed(false),
	_isCgi(false)
{
	SocketUtils::getHostAndPort(_fd, _ip, _port);
}

Event::Event(const Event &src) {}

Event::~Event(void)
{
	if (_cgiPid > 0 && !_cgiScriptEndend)
	{
		std::cout << "Tenta fazer o kill" << std::endl;
		if (kill(_cgiPid, SIGTERM) == -1)
			std::cout << "Webserv: Error terminating SGI script Event" << std::endl;
	}
	this->closeCgiWriteFd();
	this->closeCgiReadFd();
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

std::string& Event::getResponse(void)
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

// Deprecated , é para apagar esta merda ;)
void Event::setResquestBody(std::string body)
{
	_reqParsed.setRequestBody(body);
}

void Event::setReqBody(std::string body)
{
	_reqParser.bodyParse(body);
}

void Event::setParseState(int state)
{
	_parseState = state;
}

/*
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
*/

// Para remover mais tarde
bool Event::isBodyComplete(void)
{
	bool bodyComplete;

	bodyComplete = false;
	if (_reqRaw.size() == this->getBodySize())
		bodyComplete = true;
	return (bodyComplete);
}

/* void Event::createResponse(ConfigsData &configsData)
{
	std::string	reqPath;
	std::string filePath;
	std::string	contentType;

	reqPath = _reqParser.getPath();
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
} */


// New Methods
StateReqType Event::getReqState(void)
{
	return (_reqState);
}

void Event::setReqState(StateReqType reqState)
{
	_reqState = reqState;
}

void Event::updateReqRawData(std::string &req)
{
	_reqRaw += req;
}

bool Event::isReqHeaderComplete(void)
{
	if (_reqRaw.find("\r\n\r\n") != _reqRaw.npos)
		return (true);
	return (false);
}

const std::string& Event::getReqHeader(void)
{
	size_t		idx;

	idx = _reqRaw.find("\r\n\r\n");
	if (idx == _reqRaw.npos)
		return (_reqHeader);
	_reqHeader = _reqRaw.substr(0, idx + 4);
	_reqRaw.erase(0, _reqHeader.size());
	return (_reqHeader);
}

void Event::parseReqHeader(std::string &header)
{
	this->setStatusCode(_reqParser.headerParse(header));
}

void Event::setReqRaw1(std::string req)
{
	_reqRaw = req;
}

const std::string&  Event::getReqRaw1(void)
{
	return (_reqRaw);
}

const std::string&  Event::getReqRawData(void)
{
	return (_reqRaw);
}

void Event::clearReqRawData(void)
{
	_reqRaw.clear();
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

/*
void Event::printVectDebug(void)
{
	std::cout << "############## Print Response ################" << std::endl;
	for (int i = 0; i < _resVect.size(); i++)
	{
		std::cout << _resVect.at(i) << std::endl;
	}
}
*/

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
	//if (_resVect[_idx].empty() && _idx < _resVect.)
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

void Event::setRes(std::string& res)
{
	_res = res;
}

void Event::clearRes(void)
{
	_res.clear();
}

void Event::eraseRes(size_t start, size_t end)
{
	_res.erase(start, end);
}


void Event::updateRes(std::string& res)
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
	return (Timer::isTimeoutExpired(_creationTime, _timeoutSec));
	//return (true);
}

bool Event::isConnectionClose(void)
{
	if (_connectionClosed == -1)
	{
		if (!(_reqParser.getConnectionField().compare("close")))
			_connectionClosed = CONNECTION_CLOSED;
		else
			_connectionClosed = CONNECTION_KEEPALIVE;
	}
	if (_connectionClosed)
		return (true);
	return (false);
}

void Event::setConnectionClose(void)
{
	_connectionClosed = CONNECTION_CLOSED;
}


// Não usado
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

// Deprecated
int Event::getCgiFd(void)
{
	if (_cgiEx)
		return (_cgiEx->getReadFD());
	return (-1);
}


/*
int Event::getCgiWriteFd(void)
{
	if (_cgiEx)
		return (_cgiEx->getWriteFD());
	return (-1);
}

int Event::getCgiReadFd(void)
{
	if (_cgiEx)
		return (_cgiEx->getReadFD());
	return (-1);
}
*/




std::string		Event::getCgiScriptResult(void)
{
	return (_cgiScriptResult);
}

void	Event::updateCgiScriptResult(std::string& src)
{
	_cgiScriptResult += src;
}

/*
bool Event::isCgiScriptEnd(void)
{
	if (this->getCgiFd() > 0 && _state == CGI_EVENT)
	{
		if (_cgiEx->isEnded())
			return (true);
	}
	return (false);
}
*/

int Event::isCgiScriptEnd(void)
{
	if (_cgiEx && _cgiExitStatus == NO_EXIT_STATUS)
		_cgiExitStatus = _cgiEx->isEnded();
	return (_cgiExitStatus);
}

/* Getters for RequestData */

std::string	Event::getQueryString(void)
{
	return (_reqParser.getQueryString());
}

std::vector<std::string>	Event::getRequestHeaderValue(std::string key)
{
	return (_reqParsed.getHeaderValue(key));
}

std::string	Event::getReqMethod(void)
{
	return (_reqParsed.getRequestLine().at(0));
}

std::string	Event::getServerProtocol(void)
{
	return (_reqParsed.getRequestLine().at(2));
}


// Alterar esta funcao para o novo parser
/*std::string	Event::getReqContentType(void)
{
	std::string	contentType;

	if (!_reqParsed.getHeaderValue("content-type").empty())
		contentType = _reqParsed.getHeaderValue("content-type").at(0);
	return (contentType);
}*/

std::string	Event::getReqContentType(void)
{
	std::vector<std::string> contentType;

	contentType = _reqParser.getHeaderField("content-type");
	if (!contentType.empty())
		return (contentType.at(0));
	return (std::string());
}

size_t	Event::getReqContentLength(void)
{
	std::vector<std::string>	contentLength;
	size_t						len;

	contentLength = _reqParser.getHeaderField("content-length");
	if (!contentLength.empty())
	{
		std::istringstream	ss(contentLength.at(0));
		if (!(ss >> len))
			return (0);
		return (len);
	}
	return (0);
}

std::string	Event::getReqTransferEncoding(void)
{
	std::vector<std::string> transferEncoding;

	transferEncoding = _reqParser.getHeaderField("transfer-encoding");
	if (!transferEncoding.empty())
		return (transferEncoding.at(0));
	return (std::string());
}

std::string Event::getReqHost(void)
{
	std::vector<std::string> host;

	host = _reqParser.getHeaderField("host");
	if (!host.empty())
		return (host.at(0));
	return (std::string());	
}

std::string	Event::getReqLineTarget(void)
{
	return (_reqParser.getReqLineTarget());
}

std::string	Event::getReqLineHttpVersion(void)
{
	return (_reqParser.getReqLineHttpVersion());
}

std::string	Event::getReqLineMethod(void)
{
	return (_reqParser.getReqLineMethod());
}

std::string	Event::getReqLinePath(void)
{
	return (_reqParser.getReqLinePath());
}

std::string& Event::getReqBody(void)
{
	
	//return (_reqParser.getRequestBody());
	return (_reqParser.getRequestBodyRef());
}

void Event::parseHeader(std::string &header)
{
	//Função devolva true or false

	int	statusCode;


	statusCode = _reqParser.headerParse(header);
	switch (statusCode)
	{
		case 0:
			//std::cout << "---------- SUCCESS ----------" << std::endl;
			break;
		case 400:
			std::cout << "---------- 400 BAD_REQUEST ----------" << std::endl;
			break;
		case 414:
			std::cout << "---------- 414 URI_TOO_LONG ----------" << std::endl;
			break;
		case 501:
			std::cout << "---------- 501 NOT_IMPLEMENTED ----------" << std::endl;
			break;
	}

	//if (!_reqParser.headerParse(header))
	//colocar status event.setStatusCode(400) 
}


EventType Event::getOldState(void)
{
	return (_oldState);
}

EventType Event::getActualState(void)
{
	return (_actualState);
}

void Event::setActualState(EventType newState)
{
	_oldState = _actualState;
	_actualState = newState;
}

bool Event::isFinished(void)
{
	return (_finished);
}

void Event::setAsFinished(void)
{
	_finished = true;
}

bool Event::isClientDisconnect(void)
{
	return (_clientDisconnect);
}

void Event::setClientDisconnected(void)
{
	_clientDisconnect = true;
}


void Event::cgiExecute(ServerConfig *config, std::string scriptName)
{
	if (!_cgiEx)
		_cgiEx = new CGIExecuter(config, _reqParser, scriptName);
}

int Event::writeToCgi(const char *str, size_t size)
{
	if (_cgiEx)
		return (_cgiEx->writeToScript(str, size));
	return (-1);
}

int Event::readFromCgi(std::string &str)
{
	if (_cgiEx)
		return (_cgiEx->readFromScript(str));
	return (-1);
}

/*
void Event::setCgiExitStatus(int cgiExitStatus)
{
	_cgiExitStatus = cgiExitStatus;
}
*/

/*
int Event::getCgiExitStatus(void)
{
	return (_cgiExitStatus);
}
*/

void	Event::updateCgiSentChars(size_t value)
{
	_cgiSentChars += value;
}

size_t	Event::getCgiSentChars(void)
{
	return (_cgiSentChars);
}

std::string Event::getBody(void)
{
	return (_body);
}

void	Event::setBody(std::string &src)
{
	_body = src;
}

void Event::updateReqBody(std::string body)
{
	_reqParser.updateReqBody(body);
}

size_t Event::getReqBodySize(void)
{
	return (_reqParser.getRequestBodyRef().size());
}

// getErrorCode
int Event::getStatusCode(void)
{
	return (_statusCode);
}

// setErrorCode
void Event::setStatusCode(int statusCode)
{
	_statusCode = statusCode;
}

std::string Event::getIp(void)
{
	return (_ip);
}

std::string Event::getPort(void)
{
	return (_port);
}

std::string Event::getCgiBodyRes(void)
{
	return (_cgiBodyRes);
}

void	Event::setCgiBodyRes(std::string &src)
{
	_cgiBodyRes = src;
}

/*
void Event::setResourcePath(std::string resourcePath)
{
	_resourcePath = resourcePath;
}
std::string Event::getResourcePath(void)
{
	return (_resourcePath);
}
*/

void Event::setRredirectCode(int redirectCode)
{
	_redirectCode = redirectCode;
}

int Event::getRredirectCode(void)
{
	return (_redirectCode);
}

void Event::setRredirectResource(std::string redirectResource)
{
	_redirectResource = redirectResource;
}

std::string	Event::getRredirectResource(void)
{
	return (_redirectResource);
}

void Event::setFileSize(size_t fileSize)
{
	_fileSize = fileSize;
}

size_t Event::getFileSize(void)
{
	return (_fileSize);
}

void Event::setFileNumBytesRead(size_t fileNumBytesRead)
{
	_fileNumBytesRead = fileNumBytesRead;
}

void Event::updateFileNumBytesRead(size_t fileNumBytesRead)
{
	_fileNumBytesRead += fileNumBytesRead;
}

size_t Event::getFileNumBytesRead(void)
{
	return (_fileNumBytesRead);
}

void Event::setServerConfing(ServerConfig* serverConf)
{
	_serverConf = serverConf;
}

ServerConfig* Event::getServerConfing(void)
{
	return (_serverConf);
}

/*
void Event::setAutoindex(bool autoindex)
{
	_autoindex = autoindex;
}

bool Event::isAutoindex(void)
{
	return (_autoindex);
}
*/

/*
void Event::setFdCgiW(int fdCgiW)
{
	_fdCgiW = fdCgiW;
}

int Event::getFdCgiW(void)
{
	return (_fdCgiW);
}

void Event::setFdCgiR(int fdCgiR)
{
	_fdCgiR = fdCgiR;
}

int Event::getFdCgiR(void)
{
	return (_fdCgiR);
}

void Event::setPidCgi(int pidCgi)
{
	_pidCgi = pidCgi;
}

int Event::getPidCgi(void)
{
	return (_pidCgi);
}
*/

int Event::getCgiWriteFd(void)
{
	return (_cgiWriteFd);
}

void Event::setCgiWriteFd(int cgiWriteFd)
{
	_cgiWriteFd = cgiWriteFd;
}

int Event::getCgiReadFd(void)
{
	return (_cgiReadFd);
}

void Event::setCgiReadFd(int cgiReadFd)
{
	_cgiReadFd = cgiReadFd;
}

int Event::getCgiPid(void)
{
	return (_cgiPid);
}

void Event::setCgiPid(int pidCgi)
{
	_cgiPid = pidCgi;
}

ssize_t Event::getNumBytesSendCgi(void)
{
	return (_numBytesSendCgi);
}

void Event::setNumBytesSendCgi(ssize_t numBytesSendCgi)
{
	_numBytesSendCgi = numBytesSendCgi;
}

void Event::updateNumBytesSendCgi(ssize_t numBytesSendCgi)
{
	_numBytesSendCgi += numBytesSendCgi;
}

/*
void Event::closeCgiWriteFd(void)
{
	if (_cgiWriteFd < 0)
		return ;
	close(_cgiWriteFd);
	_cgiWriteFd = -1;
}

void Event::closeCgiReadFd(void)
{
	if (_cgiReadFd < 0)
		return ;
	close(_cgiReadFd);
	_cgiReadFd = -1;
}
*/

void Event::closeCgiWriteFd(void)
{
	if (_cgiWriteFd < 0 || _cgiWriteFdClosed)
		return ;
	close(_cgiWriteFd);
	_cgiWriteFdClosed = true;
}

void Event::closeCgiReadFd(void)
{
	if (_cgiReadFd < 0 || _cgiReadFdClosed)
		return ;
	close(_cgiReadFd);
	_cgiReadFdClosed = true;
}


//bool	cgiScriptEndend


int Event::getCgiExitStatus(void)
{
	return (_cgiExitStatus);
}

void Event::setCgiExitStatus(int cgiExitStatus)
{
	_cgiExitStatus = cgiExitStatus;
}

bool Event::isCgiScriptEndend(void)
{
	return (_cgiScriptEndend);
}

void Event::setCgiScriptEndend(bool cgiScriptEndend)
{
	_cgiScriptEndend = cgiScriptEndend;
}

std::string Event::getRoute(void)
{
	return (_route);
}

void Event::setRoute(std::string route)
{
	_route = route;
}

std::string Event::getRequestPath(void)
{
	return (_requestPath);
}

void Event::setRequestPath(std::string requestPath)
{
	_requestPath = requestPath;
}

std::string Event::getResourcePath(void)
{
	return (_resourcePath);
}

void Event::setResourcePath(std::string resourcePath)
{
	_resourcePath = resourcePath;
}

void Event::setIsCgi(bool isCgi)
{
	_isCgi = isCgi;
}

bool Event::isCgi(void)
{
	return (_isCgi);
}