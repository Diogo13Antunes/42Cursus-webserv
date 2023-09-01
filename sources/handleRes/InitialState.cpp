/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/01 10:09:18 by dcandeia         ###   ########.fr       */
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
	std::string resourcePath;
	std::string reqPath;



	if (event->getStatusCode())
		return (ERROR_HANDLING);
	if (!event->getCgiScriptResult().empty())
		return (CGI_RES_HANDLING);
	// verificar se o metodo é permitido.
	if (_hasRedirection(event, config))
		return (REDIRECTION_HANDLING);
	reqPath =  event->getReqLinePath();
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
	std::string	rootPath;
	std::string	aliasPath;
	std::string	index;

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
