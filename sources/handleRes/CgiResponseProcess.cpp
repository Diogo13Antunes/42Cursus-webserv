#include "CgiResponseProcess.hpp"

void	printer(std::string src, bool withNL)
{
	std::cout << src;
	if (withNL)
		std::cout << std::endl;
}

CgiResponseProcess::CgiResponseProcess(void)
{
	//Default CgiResponseProcess Constructor
}

CgiResponseProcess::~CgiResponseProcess(void)
{
	//Default CgiResponseProcess Destructor
}

StateResType	CgiResponseProcess::handle(Event *event, ServerConfig configsData)
{
	(void)configsData;
	std::vector<std::string>::iterator	it;
	std::vector<std::string>			headerVector;
	std::string							scriptRes;
	std::string							cgiBody;
	std::string							line;
	std::string							res;

	scriptRes = event->getCgiScriptResult();
	headerVector = _getHeaderVector(scriptRes);
	res = _getStatusLine(headerVector);
	for (it = headerVector.begin(); it !=  headerVector.end(); it++)
	{
		if (!StringUtils::isStringEmptyOrSpaces(*it))
		{
			line = _getResponseHeaderLine(*it);
			if (StringUtils::isStringEmptyOrSpaces(line))
			{
				res = _invalidCgiResponse();
				break;
			}
			res += line;
		}
	}
	res += "\r\n";
	if (_existContent(headerVector))
		cgiBody = _getCgiBody(scriptRes);
	event->setRes(res);
	event->setCgiBodyRes(cgiBody);
	event->setResSize(res.size() + cgiBody.size());
	return (GET_BODY);
}

/* PRIVATE METHODS */

std::vector<std::string>	CgiResponseProcess::_getHeaderVector(std::string &src)
{
	std::vector<std::string>	result;
	std::istringstream			iss(src);
	std::string					line;

	while (std::getline(iss, line))
	{
		if (StringUtils::isStringEmptyOrSpaces(line))
			break;
		result.push_back(line);
	}
	return (result);
}

std::string	CgiResponseProcess::_getStatusLine(std::vector<std::string> &src)
{
	std::vector<std::string>::iterator	it;
	std::string key;
	std::string value;
	std::string res;

	for (it = src.begin(); it !=  src.end(); it++)
	{
		key = _getKey(*it);
		if (key.compare("Status") == 0)
		{
			value = _getValue(*it);
			(*it).clear();
			break;
		}
	}
	if (value.empty())
		value = "200 OK";
	res = "HTTP/1.1 ";
	res += value;
	res += "\r\n";
	return (res);
}

std::string	CgiResponseProcess::_getKey(std::string &line)
{
	std::string	key;
	size_t	i;

	i = line.find(":");
	if (i != line.npos)
	{
		key = line.substr(0, i);
		key = StringUtils::stringTrim(key);
	}
	return (key);
}

std::string	CgiResponseProcess::_getValue(std::string &line)
{
	std::string	value;
	size_t	i;

	i = line.find(":");
	if (i != line.npos)
	{
		value = line.substr(i + 1);
		value = StringUtils::stringTrim(value);
	}
	return (value);
}

std::string	CgiResponseProcess::_invalidCgiResponse(void)
{
	std::string out;

	out = "HTTP/1.1 501 Internal Server Error\r\n";
	out += "Connection: keep-alive\r\n";
	out += "Server: webserv\r\n";
	return (out);
}

bool	CgiResponseProcess::_existContent(std::vector<std::string> &header)
{
	std::vector<std::string>::iterator	it;
	std::string							key;

	for (it = header.begin(); it != header.end(); it++)
	{
		key = _getKey(*it);
		if (key.compare("Content-Type") == 0)
			return (true);
	}
	return (false);
}

std::string	CgiResponseProcess::_getCgiBody(std::string &src)
{
	std::string body;
	size_t		i;

	i = src.find("\n\n");
	if (i != src.npos)
		body = src.substr(i + 2);
	return (body);
}

std::string	CgiResponseProcess::_getResponseHeaderLine(std::string &src)
{
	std::string	headerLine;
	std::string	key;	
	std::string	value;

	key = _getKey(src);
	value = _getValue(src);
	if (!StringUtils::isStringEmptyOrSpaces(key) && !StringUtils::isStringEmptyOrSpaces(value))
		headerLine = key + ": " + value + "\r\n";
	return (headerLine);	
}
