/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 17:38:03 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/stat.h>

#include "HeaderProcess.hpp"
#include "RequestParser.hpp"
#include "SocketUtils.hpp"
#include "ServerConfig.hpp"


static void getHostPortFromSocket(int fd, std::string& hostIP, std::string& port);

HeaderProcess::HeaderProcess(void) {}

HeaderProcess::~HeaderProcess(void) {}



// requestPath    -> path com o que vem no request
// resourcePath   -> path com o fichiro configurado na rota seja cgi ou index

// verificar primeiro se é permitido o metodo e lancar erro se necessário

// verificar o tamanho do body e lançar erro
StateReqType HeaderProcess::handle(Event *event, ConfigsData *configsData)
{
	std::string		header;
	ServerConfig	*serverConf;


	if (!event->isReqHeaderComplete())
		return (HEADER_PROCESS);
	header = event->getReqHeader();
	event->parseReqHeader(header);

	serverConf = _getServerConfig(event, configsData);
	event->setServerConfing(serverConf);

	std::string path;
	std::string route;
	std::string resourcePath;
	std::string requestPath;


	path = event->getReqLinePath();
	route = _getExtesionRoute(*serverConf, path);
	if (route.empty())
		route = _getRouteName(*serverConf, path);
	
	requestPath = _getRealPath(*serverConf, event, route);
	resourcePath = requestPath;
	if (!event->isCgi())
		resourcePath = _getPathWithIndex(*serverConf, requestPath, route);
	
	std::cout << "Route: " << route << std::endl;
	std::cout << "requestPath: " << requestPath << std::endl;
	std::cout << "resourcePath: " << resourcePath << std::endl;


	event->setRoute(route);
	event->setRequestPath(requestPath);
	event->setResourcePath(resourcePath);

	if (!event->getReqLineMethod().compare("GET"))
		return (REQUEST_END);
	if (event->getStatusCode())
		return (REQUEST_END);
	if (_isChunkedTransfer(event))
		return (CHUNKED_BODY_PROCESS);
	if (event->getReqContentLength())
		return (BODY_PROCESS);
	return (REQUEST_END);

}

ServerConfig* HeaderProcess::_getServerConfig(Event *event, ConfigsData *configsData)
{
	std::vector<ServerConfig>::iterator	it;
	std::string							ipReq;
	std::string							portReq;
	std::string							hostReq;
	ServerConfig						*serverConf;
	std::vector<ServerConfig>&			serversConf =  configsData->getServers();

	ipReq = event->getIp();
	portReq = event->getPort();
	hostReq = event->getReqHost();
	serverConf = NULL;
	for (it = serversConf.begin(); it != serversConf.end(); it++)
	{
		if (!ipReq.compare(it->getIp()) && !portReq.compare(it->getPort()))
		{
			if (!hostReq.compare(it->getServerName()))
			{
				serverConf = &(*it);
				break ;
			}
			else if (serverConf == NULL)
				serverConf = &(*it);
		}
	}
	return (serverConf);
}

std::string HeaderProcess::_getRouteName(ServerConfig& config, std::string reqPath)
{
	std::string	prevPath;

	if (config.isConfiguredRoute(reqPath))
		return (reqPath);
	prevPath = _getPreviousPath(reqPath);
	while (prevPath.compare("/"))
	{
		if (config.isConfiguredRoute(prevPath))
			return (prevPath);
		prevPath = _getPreviousPath(prevPath);
	}
	return (prevPath);
}

std::string HeaderProcess::_getExtesionRoute(ServerConfig& config, std::string reqPath)
{
	std::string	route;
	size_t		idx;

 	idx = reqPath.find_last_of('.');
	if (idx == reqPath.npos)
		return (route);
	reqPath = reqPath.erase(0, idx);
	idx = reqPath.find('/');
	if (idx != reqPath.npos)
		return (route);
	reqPath = "*" + reqPath;
	if (config.isConfiguredRoute(reqPath))
		route = reqPath;
	return (route);
}

std::string HeaderProcess::_getPreviousPath(std::string path)
{
	size_t	idx;

	if (path.size() == 1)
		return (path);
	if (path.at(path.size() - 1) == '/')
		path.erase(path.size() - 1);
	idx = path.find_last_of("/");
	if (idx != path.npos)
			path.erase(idx + 1);
	return (path);
}

std::string HeaderProcess::_getRealPath(ServerConfig& config, Event *event, std::string route)
{
	std::string realPath;
	std::string alias;
	std::string root;
	std::string cgi;
	std::string	reqPath;

	reqPath = event->getReqLinePath();
	cgi = config.getLocationCgi(route);
	if (cgi.empty())
	{
		alias = config.getLocationAlias(route);
		if (alias.empty())
			root = config.getLocationRootPath(route);
		if (root.empty() && alias.empty())
			root = config.getMasterRoot();
	}
	else
		event->setIsCgi(true);
	if (!cgi.empty())
	{
		if (!_isFolder(cgi))
			realPath = cgi;
		else 
			realPath = cgi + reqPath;
	}
	else if (!root.empty())
		realPath = root + reqPath;
	else
		realPath = alias + reqPath.substr(route.size());
	return (realPath);
}

std::string HeaderProcess::_getPathWithIndex(ServerConfig& config, std::string path, std::string route)
{
	std::string index;

	if (!_isFolder(path))
		return (path);
	index = config.getLocationIndex(route);
	if (index.empty())
	{
		if (!access((path + "/index.html").c_str(), F_OK))
			path += "/index.html";
	}
	else
		path += "/" + index;
	return (path);
}

bool HeaderProcess::_isFolder(std::string path)
{
	struct stat	pathInfo;
	int			err;

	err = stat(path.c_str(), &pathInfo);
	if (!err)
	{
		if (S_ISDIR(pathInfo.st_mode))
			return (true);
	}
	return (false);
}

bool HeaderProcess::_isChunkedTransfer(Event *event)
{
	std::string transferEconding;

	transferEconding = event->getReqTransferEncoding();
	if (!transferEconding.compare("chunked"))
		return (true);
	else
		return (false);
}