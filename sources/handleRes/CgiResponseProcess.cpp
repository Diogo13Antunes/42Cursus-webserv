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

StateResType	CgiResponseProcess::handle(Event *event, ConfigsData configsData)
{
	(void)configsData;
	std::vector<std::string>::iterator	it;
	std::vector<std::string>			headerVector;
	std::string							scriptRes;
	std::string							resBody;
	std::string							key;
	std::string							value;

	scriptRes = event->getCgiScriptResult();
	headerVector = _getHeaderVector(scriptRes);

	resBody = _getStatusLine(headerVector);
	for (it = headerVector.begin(); it !=  headerVector.end(); it++)
	{
		if (!StringUtils::isStringEmptyOrSpaces(*it))
		{
			key = _getKey(*it);
			value = _getValue(*it);
			if (StringUtils::isStringEmptyOrSpaces(key)
				|| StringUtils::isStringEmptyOrSpaces(value))
			{
				resBody = _invalidCgiResponse();
				break;
			}
			resBody += key + ": " + value + "\r\n";
		}
	}

	printer("-------------------------", true);
	printer(resBody, false);
	printer("-------------------------", true);

	event->setRes(resBody);

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
