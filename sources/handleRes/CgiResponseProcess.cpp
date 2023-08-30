#include "CgiResponseProcess.hpp"

CgiResponseProcess::CgiResponseProcess(void) {}

CgiResponseProcess::~CgiResponseProcess(void) {}

StateResType	CgiResponseProcess::handle(Event *event, ServerConfig& configsData)
{
	(void)configsData;
	HttpHeaderBuilder								header;
	std::map<std::string, std::string>::iterator	it;
	std::map<std::string, std::string>				headerMap;
	std::string										scriptRes;
	std::string										cgiBody;
	std::string										res;
	std::string										key;


	std::cout << "CgiResponseProcess" << std::endl;

	scriptRes = event->getCgiScriptResult();
	headerMap = _getHeaderMap(scriptRes);
	for (it = headerMap.begin(); it !=  headerMap.end(); it++)
	{
		key = it->first;
		StringUtils::stringToLower(key);
		if (!key.compare("status"))
			header.setStatus(it->second);
		else if (!key.compare("date"))
			header.setDate(it->second);
		else if (!key.compare("connection"));
		else if (!key.compare("content-length"));
		else if (!key.compare("server"));
		else
			header.addNewField(it->first, it->second);
	}
	if (_existContent(headerMap))
	{
		cgiBody = _getCgiBody(scriptRes);
		if (!_existContentLength(headerMap))
			header.setContentLength(cgiBody.size());
	}
	res = header.getHeader();
	event->setRes(res);
	event->setCgiBodyRes(cgiBody);
	event->setResSize(res.size() + cgiBody.size());
	return (RESPONSE);
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

	for (it = header.begin(); it !=  header.end(); it++)
	{
		key = it->first;
		StringUtils::stringToLower(key);
		if (key.compare("content-type"))	
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

std::pair<std::string, std::string>	CgiResponseProcess::_makePair(std::string &line)
{
	std::string key;
	std::string value;

	key = _getKey(line);
	value = _getValue(line);
	return (std::make_pair(key, value));
}

bool	CgiResponseProcess::_existContentLength(std::map<std::string, std::string> &map)
{
	std::map<std::string, std::string>::iterator	it;

	it = map.find("Content-Length");
	if (it != map.end())
		return (true);
	return (false);
}
