/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/28 15:13:19 by dsilveri         ###   ########.fr       */
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

	std::cout << "InitialState" << std::endl;

	if (event->getStatusCode())
		return (ERROR_HANDLING);
	
	// verificar se é cgi

	// verificar se o metodo é permitido.

	if (_hasRedirection(event, config))
		return (REDIRECT);
	
	resourcePath = _getResourceFromURLPath(config, event->getReqLinePath());
	event->setResourcePath(resourcePath);
	
	if (_isFolder(resourcePath))
		return (DIRECTORY_LISTING);
	




	// verificar buscar o resource real include root or alias

	// criar a resposta com o get 

	// fazer directory listing

	exit(0);
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
			fullPath + "index.html";
	}
	return (fullPath);
}



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