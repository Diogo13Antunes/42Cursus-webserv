/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectionHandlingState.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:14:45 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 23:03:55 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RedirectionHandlingState.hpp"
#include "HttpHeaderBuilder.hpp"
#include "configs.hpp"
#include "StringUtils.hpp"
#include <iostream>

#define MIME_TYPE_BODY	"text/html"

RedirectionHandlingState::RedirectionHandlingState(void)
{
	_redirCodes.insert(std::make_pair(301, "Moved Permanently"));
	_redirCodes.insert(std::make_pair(302, "Moved Temporarily"));
	_redirCodes.insert(std::make_pair(303, "See Other"));
	_redirCodes.insert(std::make_pair(307, "Temporary Redirect"));
	_redirCodes.insert(std::make_pair(308, "Permanent Redirect"));
}

RedirectionHandlingState::~RedirectionHandlingState(void) {}

StateResType RedirectionHandlingState::handle(Event *event, ServerConfig& config)
{
	std::string header;
	std::string body;
	std::string res;
	int			code;

	code = event->getRredirectCode();
	body = _createBody(code);
	header = _createHeader(config, code, event->getRredirectResource(), body.size());
	res = header + body;
	event->setRes(res);
	event->setResSize(res.size());
	return (RESPONSE);
}

std::string RedirectionHandlingState::_createHeader(ServerConfig& config, int code, std::string resource, int bodySize)
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
	httpHeader.setContentType(MIME_TYPE_BODY);
	httpHeader.setContentLength(bodySize);
	return (httpHeader.getHeader());
}

std::string	RedirectionHandlingState::_getStatusCode(int code)
{
	std::map<int, std::string>::iterator	it;
	std::string								status;

	it = _redirCodes.find(code);
	if (it == _redirCodes.end())
		return (status);
	status = StringUtils::toString(code) + " " + it->second;
	return (status);
}

std::string RedirectionHandlingState::_getLocation(std::string resource, std::string host, std::string port)
{
	std::string	location;
	std::string	protocol;

	StringUtils::stringTrim(resource);
	if (resource.empty())
		return (std::string());
	if (resource.at(0) != '/')
		return (resource);
	protocol = PROTOCOL;
	if (!host.compare(LOOPBACK_ADD))
		host = "localhost";
	location = protocol + "://" + host + ":" + port + resource;
	return (location);
}

std::string RedirectionHandlingState::_createBody(int code)
{
	std::string body;

	body = "<!DOCTYPE html><html><head><title>" + _getStatusCode(code) + "</title></head>";
	body += "<body><h1>" + _getStatusCode(code) + "</h1></body></html>";
	return (body);
}
