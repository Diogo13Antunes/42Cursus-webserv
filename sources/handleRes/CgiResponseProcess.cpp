#include "CgiResponseProcess.hpp"

static bool	existHeaderElement(std::map<std::string, std::string> &header, std::string element);

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
	std::map<std::string, std::string>::iterator	it;
	std::map<std::string, std::string>				headerMap;
	std::string										scriptRes;
	std::string										cgiBody;
	std::string										res;

	scriptRes = event->getCgiScriptResult();
	headerMap = _getHeaderMap(scriptRes);
	res = _getStatusLine(headerMap);
	_completeHeaderSet(headerMap);
	for (it = headerMap.begin(); it !=  headerMap.end(); it++)
		res += _getResponseHeaderLine(it->first, it->second);
	res += "\r\n";
	if (_existContent(headerMap))
		cgiBody = _getCgiBody(scriptRes);
	event->setRes(res);
	event->setCgiBodyRes(cgiBody);
	event->setResSize(res.size() + cgiBody.size());
	return (GET_BODY);
}

/* PRIVATE METHODS */

std::map<std::string, std::string>	CgiResponseProcess::_getHeaderMap(std::string &src)
{
	std::map<std::string, std::string>	result;
	std::istringstream					iss(src);
	std::string							line;
	size_t								i;

	while (std::getline(iss, line))
	{
		if (StringUtils::isStringEmptyOrSpaces(line))
			break;
		result.insert(_makePair(line));
	}
	return (result);
}

std::string	CgiResponseProcess::_getStatusLine(std::map<std::string, std::string> &src)
{
	std::map<std::string, std::string>::iterator	it;
	std::string										key;
	std::string										value;
	std::string										res;

	it = src.find("Status");
	if (it != src.end())
		value = it->second;
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

bool	CgiResponseProcess::_existContent(std::map<std::string, std::string> &header)
{
	std::map<std::string, std::string>::iterator	it;
	std::string										key;

	it = header.find("Content-Type");
	if (it != header.end())
		return (true);
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

std::string	CgiResponseProcess::_getResponseHeaderLine(std::string key, std::string value)
{
	std::string	headerLine;

	if (!StringUtils::isStringEmptyOrSpaces(key) && !StringUtils::isStringEmptyOrSpaces(value))
		headerLine = key + ": " + value + "\r\n";
	return (headerLine);	
}

std::pair<std::string, std::string>	CgiResponseProcess::_makePair(std::string &line)
{
	std::string key;
	std::string value;

	key = _getKey(line);
	value = _getValue(line);
	return (std::make_pair(key, value));
}

void	CgiResponseProcess::_completeHeaderSet(std::map<std::string, std::string> &header)
{
	if (!existHeaderElement(header, "Date"))
		header.insert(std::make_pair("Date", TimeDate::getTimeDateIMFfixdateFormat()));
	if (!existHeaderElement(header, "Connection"))
		header.insert(std::make_pair("Connection", "keep-alive"));
	if (!existHeaderElement(header, "Server"))
		header.insert(std::make_pair("Server", "webserv/1.0"));
}

/* STATIC FUNCTIONS */

static bool	existHeaderElement(std::map<std::string, std::string> &header, std::string element)
{
	std::map<std::string, std::string>::iterator it;

	it = header.find(element);
	if (it != header.end())
		return (true);
	return (false);
}
