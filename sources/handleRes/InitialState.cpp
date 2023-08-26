/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/26 09:12:18 by dsilveri         ###   ########.fr       */
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
	std::cout << "InitialState" << std::endl;

	if (event->getStatusCode())
		return (ERROR_HANDLING);
	
	// verificar se o metodo é permitido.

	if (_hasRedirection(event, config))
		return (REDIRECT);
	

	


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
