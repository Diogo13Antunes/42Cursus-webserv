/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:10:31 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/14 10:59:56 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketUtils.hpp"

#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

void SocketUtils::getHostAndPort(int fd, std::string& hostIP, std::string& port)
{
	struct sockaddr_in	addr;
	socklen_t			addrlen;
	std::stringstream	ss;

	
	addrlen = (socklen_t) sizeof(addr);
	if (getsockname(fd, (struct sockaddr *)&addr, &addrlen) == -1)
		return ;
	hostIP.assign(inet_ntoa(addr.sin_addr));
	ss << ntohs(addr.sin_port);
	ss >> port;
}

std::string SocketUtils::getHostIP(int fd)
{
	struct sockaddr_in	addr;
	socklen_t			addrlen;
	std::stringstream	ss;
	std::string			host;
	
	addrlen = (socklen_t) sizeof(addr);
	if (getsockname(fd, (struct sockaddr *)&addr, &addrlen) == -1)
		return (host);
	host = inet_ntoa(addr.sin_addr);
	return (host);
}

std::string SocketUtils::getPort(int fd)
{
	struct sockaddr_in	addr;
	socklen_t			addrlen;
	std::stringstream	ss;
	std::string			port;

	addrlen = (socklen_t) sizeof(addr);
	if (getsockname(fd, (struct sockaddr *)&addr, &addrlen) == -1)
		return (port);
	ss << ntohs(addr.sin_port);
	ss >> port;
	return (port);
}

std::string	SocketUtils::getIpAddress(std::string host, std::string port)
{
	struct addrinfo		hints, *result;
	struct sockaddr_in	*ipv4;
	std::string			ip;

    memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(host.c_str(), port.c_str(), &hints, &result) != 0)
		return (ip);
	if (result->ai_family == AF_INET)
	{
		ipv4 = (struct sockaddr_in *)result->ai_addr;
		ip = inet_ntoa(ipv4->sin_addr);
	}
	freeaddrinfo(result);
	return (ip);
}
