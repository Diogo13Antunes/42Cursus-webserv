/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectionHandler.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:14:45 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/18 19:42:36 by dsilveri         ###   ########.fr       */
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
	_redirCodes.insert(std::make_pair(302, "Found"));
}

RedirectionHandler::~RedirectionHandler(void) {}

StateResType RedirectionHandler::handle(Event *event, ServerConfig config)
{
	std::string header;
	std::string	resource;
	int			code;
	
	config.getRedirectionInfo(event->getReqLinePath(), code, resource);

	std::cout << "recurso: " << resource << std::endl;
	std::cout << "code: " << code << std::endl;

	header = _createHeader(config, code, resource);
	//std::cout << _createHeader(code, resource) << std::endl;

	event->setRes(header);


	return (RESPONSE);
}


/*
HTTP/1.1 301 Moved Permanently
Server: nginx/1.18.0 (Ubuntu)
Date: Fri, 18 Aug 2023 13:15:50 GMT
Content-Type: text/html
Content-Length: 178
Location: http://localhost:8080/sources/
Connection: keep-alive
*/

/*
std::string RedirectionHandler::_createHeader(ServerConfig config, int code, std::string resource)
{
	HttpHeaderBuilder	httpHeader;
	std::string			protocol;
	std::string			location;

	httpHeader.setStatus("301 Moved Permanently");
	
	//protocol = PROTOCOL;
	//location = protocol + "://" + config.getHost() + ":" + config.getPort() + resource;

	std::cout << "host: " << config.getHost() << std::endl;
	std::cout << "port: " << config.getPort() << std::endl;
	std::cout << "resource: " << resource << std::endl;

	//location = protocol + "://" + "127.0.0.1" + ":" + "8080" + resource;

	httpHeader.setLocation("http://127.0.0.1:8080/test.html");


	return (httpHeader.getHeader());
}
*/

std::string RedirectionHandler::_createHeader(ServerConfig config, int code, std::string resource)
{
	HttpHeaderBuilder	httpHeader;
	std::string			protocol;
	std::string			location;

	location = _createHeader(resource, config.getHost(), config.getPort());

	std::cout << "Location: " << location << std::endl;


	httpHeader.setStatus("301 Moved Permanently");
	httpHeader.setLocation(location);

	return (httpHeader.getHeader());
}

std::string RedirectionHandler::_createHeader(std::string resource, std::string host, std::string port)
{
	std::string	location;
	std::string	protocol;
	size_t		idx;

	// se o primeiro char for diferente "/" não necessita de receber o URL

	// se não for barra necessita do URL completo

	if (resource.empty())
		return (resource);
	StringUtils::stringTrim(resource);

	//if (!resource.find("http://") || !resource.find("https://"))
	//	return (resource);
	if (resource.at(0) != '/')
		return (resource);
	protocol = PROTOCOL;
	if (!host.compare(LOOPBACK_ADD))
		host = "localhost";
	location = protocol + "://" + host + ":" + port + resource;
	return (location);
}
