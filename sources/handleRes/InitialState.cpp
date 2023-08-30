/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/30 16:01:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InitialState.hpp"
#include <iostream>
#include <sys/stat.h>

#define MOVED_PERMANENTLY	301



InitialState::InitialState(void) {}

InitialState::~InitialState(void) {}

StateResType InitialState::handle(Event *event, ServerConfig config)
{
	std::string resourcePath;
	std::string reqPath;

	if (event->getStatusCode())
		return (ERROR_HANDLING);
	
	// verificar se é cgi

	// verificar se o metodo é permitido.


	if (_hasRedirection(event, config))
		return (REDIRECT);
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




	// verificar buscar o resource real include root or alias

	// criar a resposta com o get 

	// fazer directory listing


	return (RESPONSE);
	//return (CREATE_HEADER);
}

bool InitialState::_hasRedirection(Event *event, ServerConfig config)
{
	std::string	path;
	std::string	resource;
	int			code;
	
	code = 0;
	path = event->getReqLinePath();
	config.getRedirectionInfo(path, code, resource);
	if (!code && path.at(path.size() - 1) != '/')
	{
		if (config.isConfiguredRoute(path) || _isFolder(config.getMasterRoot() + path))
		{
			resource = path + "/";
			code = MOVED_PERMANENTLY;
		}
	}
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
	if (rootPath.empty())
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
		//std::cout << "Rota anterior: " << prevPath << std::endl;

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


/*
std::string InitialState::_getResourceFromURLPath(ServerConfig& config, std::string path)
{
	std::string fullPath;
	std::string	rootPath;
	std::string	aliasPath;
	std::string	index;
	std::string prevRoute;


	std::cout << "reqPath:  " << path << std::endl;

	prevRoute = path;
	while (!prevRoute.empty())
	{
		aliasPath = config.getLocationAlias(prevRoute);
		if (aliasPath.empty())
			rootPath = config.getLocationRootPath(prevRoute);
		if (!aliasPath.empty() || !rootPath.empty())
			break;
		prevRoute = _getPreviousRoute(prevRoute);
	}
	if (aliasPath.empty() || rootPath.empty())
		rootPath = config.getMasterRoot();
	if (!aliasPath.empty())
		fullPath = aliasPath;
	else
		fullPath = rootPath + path;
	if (path.at(path.size() - 1) == '/')
		index = config.getLocationIndex(path);
	if (!index.empty())
	{
		std::cout << "adiciona o index: " << index << std::endl;
		fullPath += index;
	}
	else
	{
		if (access((fullPath + "index.html").c_str(), F_OK) == 0)
			fullPath += "index.html";
	}
	std::cout << "fullPath: " << fullPath << std::endl;
	return (fullPath);
}
*/


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



/*

bool DirectoryListingState::_checkDirectoryAccess(Event *event, ServerConfig config)
{
	std::string	route;
	std::string	autoIndex;

	route = event->getReqLinePath();
	autoIndex = config.getLocationAutoIndex(route);
	while (autoIndex.empty())
	{
		_getPreviousRoute(route);
		if (route.size() == 1 && route.at(0) == '/')
			break;
		autoIndex = config.getLocationAutoIndex(route);
	}
	if (!autoIndex.compare(AUTOINDEX_ON))
		return (true);
	return (false);
}

*/

/*
std::string InitialState::_getResourceFromURLPath(ServerConfig& config, std::string path, ResourceType& type)
{
	std::string rootPath;
	std::string index;
	std::string fullPath;
	std::string fullPathIndex;
	std::string alias;

	std::string newPath;
	size_t lastBarIdx;


	std::cout << "PATH: " << path << std::endl;

	rootPath = config.getLocationRootPath(path);
	if(rootPath.empty())
	{
		lastBarIdx = path.find_last_of("/");
		newPath = path.substr(0, lastBarIdx);
		alias = config.getLocationAlias(newPath);
		if (!alias.empty())
			alias +=  path.substr(lastBarIdx);
	}
	else
		alias = config.getLocationAlias(path);

	if (rootPath.empty() && alias.empty())
		rootPath = config.getMasterRoot();
		
	if (!alias.empty())
		fullPath = alias;
	else
		fullPath = rootPath + path;
	index = config.getLocationIndex(path);
	if (!index.empty())
		fullPath += "/" + index;
	if (!_isFolder(fullPath))
	{
		type = FILE_TYPE;
		return (fullPath);
	}
	type = FOLDER_TYPE;
	fullPathIndex = fullPath + "/index.html";
	if (access(fullPathIndex.c_str(), F_OK) == 0)
	{
		type = FILE_TYPE;
		return (fullPathIndex);
	}
	return (fullPath);
}
*/