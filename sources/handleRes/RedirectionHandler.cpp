/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectionHandler.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:14:45 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/19 17:41:32 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RedirectionHandler.hpp"
#include "HttpHeaderBuilder.hpp"
#include "configs.hpp"
#include "StringUtils.hpp"
#include <iostream>

RedirectionHandler::RedirectionHandler(void)
{
	_redirCodes.insert(std::make_pair(301, "Moved Permanently"));
	_redirCodes.insert(std::make_pair(302, "Moved Temporarily"));
	_redirCodes.insert(std::make_pair(303, "See Other"));
	_redirCodes.insert(std::make_pair(307, "Temporary Redirect"));
	_redirCodes.insert(std::make_pair(308, "Permanent Redirect"));
}

RedirectionHandler::~RedirectionHandler(void) {}

StateResType RedirectionHandler::handle(Event *event, ServerConfig config)
{
	std::string header;
	std::string	resource;
	int			code;
	
	config.getRedirectionInfo(event->getReqLinePath(), code, resource);
	header = _createHeader(config, code, resource);
	event->setRes(header);
	return (RESPONSE);
}

std::string RedirectionHandler::_createHeader(ServerConfig config, int code, std::string resource)
{
	HttpHeaderBuilder	httpHeader;
	std::string			location;
	std::string			statusCode;

	
	statusCode = _getStatusCode(code);
	if (statusCode.empty())
	{
		httpHeader.setStatus(StringUtils::toString(code));
		return (httpHeader.getHeader());
	}
	location = _getLocation(resource, config.getHost(), config.getPort());
	httpHeader.setStatus(statusCode);
	httpHeader.setLocation(location);
	return (httpHeader.getHeader());
}

std::string	RedirectionHandler::_getStatusCode(int code)
{
	std::map<int, std::string>::iterator	it;
	std::string								status;

	it = _redirCodes.find(code);
	if (it == _redirCodes.end())
		return (status);
	status = StringUtils::toString(code) + " " + it->second;
	return (status);
}

std::string RedirectionHandler::_getLocation(std::string resource, std::string host, std::string port)
{
	std::string	location;
	std::string	protocol;

	StringUtils::stringTrim(resource);
	if (resource.empty())
		return (" ");
	if (resource.at(0) != '/')
		return (resource);
	protocol = PROTOCOL;
	if (!host.compare(LOOPBACK_ADD))
		host = "localhost";
	location = protocol + "://" + host + ":" + port + resource;
	return (location);
}
