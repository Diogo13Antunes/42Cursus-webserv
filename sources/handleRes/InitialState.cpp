/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/06 09:48:31 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InitialState.hpp"
#include <iostream>
#include <sys/stat.h>

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
	if (!event->getCgiScriptResult().empty())
		return (CGI_RES_HANDLING);
	reqPath = event->getReqLinePath();
	route = _getRouteName(config, reqPath);
	realPath = _getRealPath(config, reqPath, route);
	if (_hasForcedRedirection(event, reqPath, realPath, route) || _hasConfRedirection(event, config, route))
		return (REDIRECTION_HANDLING);
	realPath = _getPathWithIndex(config, realPath, route);
	event->setResourcePath(realPath);
	if (event->getStatusCode())
		return (ERROR_HANDLING);
	if (!_isValidFile(event, realPath))
		return (ERROR_HANDLING);
	if (!_isValidMethod(event, config, route))
		return (ERROR_HANDLING);
	if (_isFolder(realPath))
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


bool InitialState::_isFolder(std::string path)
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

std::string InitialState::_getPathWithIndex(ServerConfig& config, std::string path, std::string route)
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

bool InitialState::_isMethodImplemented(std::string method)
{
	std::string	implMethods;
	
	implMethods = IMPLEMENTED_METHODS;
	if (implMethods.find(method) != implMethods.npos)
		return (true);
	return (false);
}

bool InitialState::_hasForcedRedirection(Event *event, std::string reqPath, std::string realPath, std::string route)
{
	std::string	method;
	method = event->getReqLineMethod();
	if (reqPath.at(reqPath.size() - 1) != '/')
	{
		if (route.at(route.size() - 1) == '/')
			route.erase(route.size() - 1);
		if (_isFolder(realPath) || !reqPath.compare(route))
		{
			if (!method.compare("GET"))
			{
				event->setRredirectCode(MOVED_PERMANENTLY);
				event->setRredirectResource(reqPath + "/");
				return (true);
			}
			else
			{
				event->setRredirectCode(FORBIDEN_CODE);
				return (false);
			}
		}
	}
	return (false);
}

bool InitialState::_hasConfRedirection(Event *event, ServerConfig& config, std::string route)
{
	std::string	resource;
	int			code;

	config.getRedirectionInfo(route, code, resource);
	if (code && !resource.empty())
	{
		event->setRredirectCode(code);
		event->setRredirectResource(resource);
		return (true);
	}
	return (false);
}

bool InitialState::_isValidMethod(Event *event, ServerConfig& config, std::string route)
{
	std::string	method;
	int			acceptMethod;
	
	method = event->getReqLineMethod();
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