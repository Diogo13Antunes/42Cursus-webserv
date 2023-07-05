/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaderBuilder.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:34:03 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/05 18:52:49 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpHeaderBuilder.hpp"

#include <iostream>
#include <sstream>
#include <ctime>

HttpHeaderBuilder::HttpHeaderBuilder(void): 
	_contentLength(0), 
	_status("200 OK")
{
	_getDateNow();
	//Default HttpHeaderBuilder Constructor
}

HttpHeaderBuilder::HttpHeaderBuilder(const HttpHeaderBuilder &src)
{
	//HttpHeaderBuilder Copy Constructor
}

HttpHeaderBuilder::~HttpHeaderBuilder(void)
{
	//Default HttpHeaderBuilder Destructor
}

/*
HttpHeaderBuilder &HttpHeaderBuilder::operator=(const HttpHeaderBuilder &src)
{
	//HttpHeaderBuilder Copy Assignment Operator
}
*/

void HttpHeaderBuilder::setStatus(std::string status)
{
	_status = status;
}

void HttpHeaderBuilder::setContentType(std::string contentType)
{
	_contentType = contentType;
}

void HttpHeaderBuilder::setServerName(std::string serverName)
{
	_serverName = serverName;
}

void  HttpHeaderBuilder::setDate(std::string date)
{
	_date = date;
}

void HttpHeaderBuilder::setContentLength(int contentLength)
{
	_contentLength = contentLength;
}

std::string	HttpHeaderBuilder::getHeader(void)
{
	std::string			header;
	std::stringstream	contentLength;

	contentLength << _contentLength;
	header = "HTTP/1.1 " + _status + "\r\n";
	header += "content-length: " + contentLength.str() + "\r\n";
	if (!_contentType.empty())
		header += "content-Type: " + _contentType + "\r\n";
	if (!_serverName.empty())
		header += "server: " + _serverName + "\r\n";
	if (!_date.empty())
		header += "date: " + _date + "\r\n";
	header += "\r\n";
	return (header);
}

std::string HttpHeaderBuilder::_getDateNow(void)
{
	std::string timeNow;
	struct tm	time;
	return (timeNow);
}