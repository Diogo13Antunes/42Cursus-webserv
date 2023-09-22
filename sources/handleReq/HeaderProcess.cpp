/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 19:35:56 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeaderProcess.hpp"
#include "RequestParser.hpp"
#include "SocketUtils.hpp"
#include "ServerConfig.hpp"
#include "FileSystemUtils.hpp"
#include "configs.hpp"

#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

static void getHostPortFromSocket(int fd, std::string& hostIP, std::string& port);

HeaderProcess::HeaderProcess(void) {}

HeaderProcess::~HeaderProcess(void) {}

StateReqType HeaderProcess::handle(Event *event, ConfigsData *configsData)
{
	ServerConfig	*serverConf;
	std::string		header;
	size_t			maxBodySize;
	size_t			contentLength;

	if (!event->isReqHeaderComplete())
		return (HEADER_PROCESS);
	header = event->getReqHeader();
	event->parseReqHeader(header);	
	serverConf = _getServerConfig(event, configsData);
	event->setServerConfing(serverConf);
	if (!_isProtocolSupported(event->getReqLineHttpVersion()))
	{
		event->setStatusCode(HTTP_VERSION_NOT_SUPPORTED_CODE);
		return (REQUEST_END);
	}
	_setPathAndRouteInfo(event, *serverConf);
	maxBodySize = serverConf->getLocationBodySize(event->getRoute());
	contentLength = event->getReqContentLength();
	if (contentLength > maxBodySize)
	{
		event->setStatusCode(CONTENT_TOO_LARGE_CODE);
		return (REQUEST_END);
	}
	if (event->getStatusCode())
		return (REQUEST_END);
	if (_isChunkedTransfer(event))
		return (CHUNKED_BODY_PROCESS);
	return (BODY_PROCESS);
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

std::string HeaderProcess::_getRealPath(ServerConfig& config, Event *event, bool isExtesionRoute)
{
	std::string realPath;
	std::string alias;
	std::string root;
	std::string cgi;
	std::string	reqPath;
	std::string route;

	route = event->getRoute();
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
	if (!cgi.empty())
	{
		if (!FileSystemUtils::isFolder(cgi))
			realPath = cgi;
		else 
			realPath = cgi + reqPath;
		if (isExtesionRoute || reqPath.at(reqPath.size() - 1) == '/')
			event->setIsCgi(true);
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

	if (!FileSystemUtils::isFolder(path))
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

bool HeaderProcess::_isChunkedTransfer(Event *event)
{
	std::string transferEconding;

	transferEconding = event->getReqTransferEncoding();
	if (!transferEconding.compare("chunked"))
		return (true);
	else
		return (false);
}

void HeaderProcess::_setPathAndRouteInfo(Event *event, ServerConfig& serverConf)
{
	std::string path;
	std::string route;
	std::string	routeExt;
	std::string requestPath;
	std::string resourcePath;

	path = event->getReqLinePath();
	route = _getRouteName(serverConf, path);
	if (route.empty() || !route.compare("/"))
		routeExt = _getExtesionRoute(serverConf, path);
	if (!routeExt.empty())
		route = routeExt;
	if (routeExt.empty() && !serverConf.isLocationAcceptedMethod(route, event->getReqLineMethod()))
		routeExt = _getExtesionRoute(serverConf, path);
	if (!routeExt.empty())
		route = routeExt;
	event->setRoute(route);
	requestPath = _getRealPath(serverConf, event, !routeExt.empty());
	resourcePath = requestPath;
	if (!event->isCgi())
		resourcePath = _getPathWithIndex(serverConf, requestPath, route);
	event->setRequestPath(requestPath);
	event->setResourcePath(resourcePath);
	//std::cout << "route: " << route << std::endl;
	//std::cout << "requestPath: " << requestPath << std::endl;
	//std::cout << "resourcePath: " << resourcePath << std::endl;
}

bool HeaderProcess::_isProtocolSupported(std::string protocol)
{
	if (!protocol.compare("HTTP/1.1") || !protocol.compare("HTTP/1.0"))
		return (true);
	return (false);
}