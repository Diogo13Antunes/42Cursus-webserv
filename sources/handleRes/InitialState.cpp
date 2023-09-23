/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 21:52:55 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InitialState.hpp"
#include "FileSystemUtils.hpp"
#include "configs.hpp"
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

#define MOVED_PERMANENTLY	301

InitialState::InitialState(void) {}

InitialState::~InitialState(void) {}

StateResType InitialState::handle(Event *event, ServerConfig& config)
{
	std::string	reqPath;
	std::string realPath;
	std::string	route;
	
	if (event->getStatusCode())
		return (ERROR_HANDLING);
	if (event->getCgiExitStatus())
	{
		event->setStatusCode(500);
		return (ERROR_HANDLING);
	}
	route = event->getRoute();
	realPath = event->getResourcePath();
	if (event->isCgi())
		return (CGI_RES_HANDLING);
	if (_hasForcedRedirection(event, config) || _hasConfRedirection(event, config))
		return (REDIRECTION_HANDLING);
	event->setResourcePath(realPath);
	if (event->getStatusCode())
		return (ERROR_HANDLING);
	if (!_isValidFile(event, realPath))
		return (ERROR_HANDLING);
	if (!_isValidMethod(event, config))
		return (ERROR_HANDLING);
	if (FileSystemUtils::isFolder(realPath))
	{
		if (config.getLocationAutoIndex(route))
			return (DIRECTORY_LISTING);
		else
		{
			event->setStatusCode(FORBIDEN_CODE);
			return (ERROR_HANDLING);	
		}
	}
	return (STATIC_FILE_HANDLING);
}

std::string InitialState::_getPreviousPath(std::string path)
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

std::string InitialState::_getRouteName(ServerConfig& config, std::string reqPath)
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

std::string InitialState::_getRealPath(ServerConfig& config, std::string reqPath, std::string route)
{
	std::string realPath;
	std::string alias;
	std::string root;

	alias = config.getLocationAlias(route);
	if (alias.empty()) {
		root = config.getLocationRootPath(route);
	}
    if (root.empty() && alias.empty()) {
        root = config.getMasterRoot();
	}
	if (!root.empty())
		realPath = root + reqPath;
	else
		realPath = alias + reqPath.substr(route.size());
	return (realPath);
}

std::string InitialState::_getPathWithIndex(ServerConfig& config, std::string path, std::string route)
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

bool InitialState::_isMethodImplemented(std::string method)
{
	std::string	implMethods;
	
	implMethods = IMPLEMENTED_METHODS;
	if (implMethods.find(method) != implMethods.npos)
		return (true);
	return (false);
}

bool InitialState::_hasForcedRedirection(Event *event, ServerConfig& config)
{
	std::string	method;
	std::string reqPath;
	std::string realPath;
	std::string route;

	method = event->getReqLineMethod();
	reqPath = event->getReqLinePath();
	realPath = event->getRequestPath();
	route = event->getRoute();
	if (reqPath.at(reqPath.size() - 1) != '/')
	{
		if (route.at(route.size() - 1) == '/')
			route.erase(route.size() - 1);
		if (FileSystemUtils::isFolder(realPath) || !reqPath.compare(route) || !config.getLocationCgi(route).empty())
		{
			if (!method.compare("GET"))
			{
				event->setRredirectCode(MOVED_PERMANENTLY);
				event->setRredirectResource(reqPath + "/");
				return (true);
			}
			else
			{
				event->setStatusCode(FORBIDEN_CODE);
				return (false);
			}
		}
	}
	return (false);
}

bool InitialState::_hasConfRedirection(Event *event, ServerConfig& config)
{
	std::string	resource;
	int			code;

	config.getRedirectionInfo(event->getRoute(), code, resource);
	if (code && !resource.empty())
	{
		event->setRredirectCode(code);
		event->setRredirectResource(resource);
		return (true);
	}
	return (false);
}

bool InitialState::_isValidMethod(Event *event, ServerConfig& config)
{
	std::string	method;
	std::string	route;
	int			acceptMethod;
	
	method = event->getReqLineMethod();
	route = event->getRoute();
	acceptMethod = config.isLocationAcceptedMethod(route, method);
	if (!acceptMethod)
	{
		event->setStatusCode(NOT_ALLOWED_CODE);
		return (false);
	}
	if (!_isMethodImplemented(method))
	{
		event->setStatusCode(NOT_IMPLEMENTED_CODE);
		return (false);
	}
	else if (event->getCgiScriptResult().empty() && method.compare("GET"))
	{
		event->setStatusCode(FORBIDEN_CODE);
		return (false);
	}
	return (true);
}

bool InitialState::_isValidFile(Event *event, std::string path)
{
	if (access(path.c_str(), F_OK))
	{
		event->setStatusCode(NOT_FOUND_CODE);
		return (false);
	}
	if (access(path.c_str(), R_OK))
	{
		event->setStatusCode(FORBIDEN_CODE);
		return (false);
	}
	return (true);
}