/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/04 16:09:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InitialState.hpp"
#include <iostream>
#include <sys/stat.h>

#define MOVED_PERMANENTLY	301

InitialState::InitialState(void) {}

InitialState::~InitialState(void) {}

/*
StateResType InitialState::handle(Event *event, ServerConfig& config)
{
	std::string reqPath;
	std::string resourcePath;
	std::string	method;
	int			acceptMethod;

	method = event->getReqLineMethod();
	if (event->getStatusCode())
		return (ERROR_HANDLING);
	if (!event->getCgiScriptResult().empty())
		return (CGI_RES_HANDLING);
	if (_hasRedirection(event, config))
		return (REDIRECTION_HANDLING);

	reqPath =  event->getReqLinePath();
	acceptMethod = config.isLocationAcceptedMethod(reqPath, method);
	if (!acceptMethod)
	{
		event->setStatusCode(405);
		return (ERROR_HANDLING);
	}

	
	resourcePath = _getResourceFromURLPath(config, reqPath);
	event->setResourcePath(resourcePath);
	if (_isFolder(resourcePath))
		return (DIRECTORY_LISTING);
	if (reqPath.at(reqPath.size() - 1) != '/' && access(resourcePath.c_str(), F_OK))
	{
		resourcePath = _getPreviousRouteResourcePath(config, reqPath);
		event->setResourcePath(resourcePath);
	}
	if (access(resourcePath.c_str(), F_OK))
	{
		event->setStatusCode(NOT_FOUND_CODE);
		return (ERROR_HANDLING);
	}
	if (access(resourcePath.c_str(), R_OK))
	{
		event->setStatusCode(FORBIDEN_CODE);
		return (ERROR_HANDLING);
	}
	return (STATIC_FILE_HANDLING);
}
*/

/*
bool InitialState::_hasRedirection(Event *event, ServerConfig& config)
{
	std::string	path;
	std::string	resource;
	int			code;
	
	code = 0;
	path = event->getReqLinePath();
	if (!code && path.at(path.size() - 1) != '/')
	{
		if (config.isConfiguredRoute(path) || _isFolder(config.getMasterRoot() + path))
		{
			resource = path + "/";
			code = MOVED_PERMANENTLY;
		}
	}
	if (!code)
		config.getRedirectionInfo(path, code, resource);
	if (code && !resource.empty())
	{
		event->setRredirectCode(code);
		event->setRredirectResource(resource);
		return (true);
	}
	return (false);
}
*/

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

std::string InitialState::_getResourceFromURLPath(ServerConfig& config, std::string path)
{
    std::string fullPath;
    std::string    rootPath;
    std::string    aliasPath;
    std::string    index;

    aliasPath = config.getLocationAlias(path);
    if (aliasPath.empty())
        rootPath = config.getLocationRootPath(path);
    if (rootPath.empty() && aliasPath.empty())
        rootPath = config.getMasterRoot();
    if (!aliasPath.empty())
        fullPath = aliasPath;
    else
        fullPath = rootPath + path;
    index = config.getLocationIndex(path);
    if (!index.empty())
        fullPath += index;
    else
    {
        if (access((fullPath + "index.html").c_str(), F_OK) == 0)
            fullPath += "index.html";
    }
    return (fullPath);
}

std::string InitialState::_getPreviousRouteResourcePath(ServerConfig& config, std::string path)
{
	std::string fileName;
	std::string prevPath;
	std::string	aliasPath;
	size_t		idx;

	idx = path.find_last_of("/");
	if (idx != path.npos)
		fileName = path.substr(idx + 1);
	prevPath = _getPreviousRoute(path);
	while (!prevPath.empty())
	{
		aliasPath = config.getLocationAlias(prevPath);
		if (!aliasPath.empty())
		{
			aliasPath += fileName;
			break;
		}
		prevPath = _getPreviousRoute(prevPath);
	}
	return (aliasPath);
}

std::string InitialState::_getPreviousRoute(std::string path)
{
	size_t		idx;

	if (path.size() == 1)
		return (std::string());
	if (path.at(path.size() - 1) == '/')
		path.erase(path.size() - 1);
	idx = path.find_last_of("/");
	if (idx != path.npos && idx > 0)
		path.erase(idx);
	else if (idx != path.npos)
		return (std::string());
	return (path);
}




// New Functions

StateResType InitialState::handle(Event *event, ServerConfig& config)
{
	std::string	reqPath;
	std::string realPath;
	std::string	route;
	std::string	method;
	int			acceptMethod;

	if (event->getStatusCode())
		return (ERROR_HANDLING);
	reqPath = event->getReqLinePath();
	route = _getRouteName(config, reqPath);
	method = event->getReqLineMethod();
	acceptMethod = config.isLocationAcceptedMethod(route, method);
	realPath = _getRealPath(config, reqPath, route);
	if (_hasForcedRedirection(event, reqPath, realPath) || _hasConfRedirection(event, config, route))
		return (REDIRECTION_HANDLING);
	realPath = _getPathWithIndex(config, realPath, route);
	event->setResourcePath(realPath);

	//Verificação de erros
	if (!acceptMethod)
	{
		event->setStatusCode(NOT_ALLOWED_CODE);
		return (ERROR_HANDLING);
	}
	else
	{
		if (!_isMethodImplemented(method))
		{
			event->setStatusCode(NOT_IMPLEMENTED_CODE);
			return (ERROR_HANDLING);
		}
		else if (event->getCgiScriptResult().empty() && method.compare("GET"))
		{
			event->setStatusCode(FORBIDEN_CODE);
			return (ERROR_HANDLING);
		}
	}
	if (access(realPath.c_str(), F_OK))
	{
		event->setStatusCode(NOT_FOUND_CODE);
		return (ERROR_HANDLING);
	}
	if (access(realPath.c_str(), R_OK))
	{
		event->setStatusCode(FORBIDEN_CODE);
		return (ERROR_HANDLING);
	}


	if (_isFolder(realPath))
	{
		if (!config.getLocationAutoIndex(route).compare("on"))
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


std::string InitialState::_getRealPath1(ServerConfig& config, std::string reqPath, std::string route)
{
	std::string realPath;
	std::string alias;
	std::string root;
	std::string index;

	alias = config.getLocationAlias(route);
	if (alias.empty())
		root = config.getLocationRootPath(route);
    if (root.empty() && alias.empty())
        root = config.getMasterRoot();
	if (!root.empty())
		realPath = root + reqPath;
	else
		realPath = alias + reqPath.substr(route.size());
	if (_isFolder(realPath))
	{
		index = config.getLocationIndex(route);
		if (index.empty())
		{
			if (!access((realPath + "/index.html").c_str(), F_OK))
				realPath += "/index.html";
		}
		else
			realPath += "/" + index;
	}
	return (realPath);
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

/*
bool InitialState::_hasRedirection(Event *event, ServerConfig& config, std::string path, std::string route)
{
	std::string	path;
	std::string	resource;
	int			code;
	
	code = 0;
	path = event->getReqLinePath();
	if (path.at(path.size() - 1) != '/')
	{
		if (_isFolder(path))
		{
			resource = path + "/";
			code = MOVED_PERMANENTLY;
		}
	}
	if (!code)
		config.getRedirectionInfo(route, code, resource);
	if (code && !resource.empty())
	{
		event->setRredirectCode(code);
		event->setRredirectResource(resource);
		return (true);
	}
	return (false);
}*/

bool InitialState::_hasForcedRedirection(Event *event, std::string reqPath, std::string realPath)
{
	std::string	method;

	method = event->getReqLineMethod();
	if (reqPath.at(reqPath.size() - 1) != '/' && !method.compare("GET"))
	{
		if (_isFolder(realPath))
		{
			event->setRredirectCode(MOVED_PERMANENTLY);
			event->setRredirectResource(reqPath + "/");
			return (true);
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
