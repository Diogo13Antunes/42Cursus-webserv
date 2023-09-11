/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 11:42:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "HeaderProcess.hpp"
#include "RequestParser.hpp"
#include "SocketUtils.hpp"
#include "ServerConfig.hpp"

static void getHostPortFromSocket(int fd, std::string& hostIP, std::string& port);

HeaderProcess::HeaderProcess(void) {}

HeaderProcess::~HeaderProcess(void) {}

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

	std::string route;
	std::string resourcePath;
	std::string requestedPath;

	route = _getRouteName(*serverConf, event->getReqLinePath());
	resourcePath = _getRealPath(*serverConf, event->getReqLinePath(), route);

	event->setRoute(route);
	event->setResourcePath(resourcePath);

	std::cout << "Route: " << route << std::endl;
	std::cout << "resourcePath: " << resourcePath << std::endl;


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

std::string HeaderProcess::_getRealPath(ServerConfig& config, std::string reqPath, std::string route)
{
	std::string realPath;
	std::string alias;
	std::string root;

	alias = config.getLocationAlias(route);
	if (alias.empty())
		root = config.getLocationRootPath(route);
    if (root.empty() && alias.empty())
        root = config.getMasterRoot();
	if (!root.empty())
		realPath = root + reqPath;
	else
		realPath = alias + reqPath.substr(route.size());
	return (realPath);
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