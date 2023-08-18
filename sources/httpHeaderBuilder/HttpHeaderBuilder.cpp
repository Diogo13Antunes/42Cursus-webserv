/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaderBuilder.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:34:03 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/18 16:29:38 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpHeaderBuilder.hpp"
#include "TimeDate.hpp"
#include "configs.hpp"
#include <iostream>
#include <sstream>
#include <ctime>


HttpHeaderBuilder::HttpHeaderBuilder(void): 
	_contentLength(0), 
	_status("200 OK"),
	_connection("keep-alive"),
	_date(TimeDate::getTimeDateIMFfixdateFormat())
{}

HttpHeaderBuilder::~HttpHeaderBuilder(void) {}

void HttpHeaderBuilder::setStatus(std::string status)
{
	_status = status;
}

void HttpHeaderBuilder::setContentType(std::string contentType)
{
	_contentType = contentType;
}

void  HttpHeaderBuilder::setDate(std::string date)
{
	_date = date;
}

void HttpHeaderBuilder::setConnection(std::string connection)
{
	_connection = connection;
}

void HttpHeaderBuilder::setTransferEncoding(std::string transferEncoding)
{
	_transferEncoding = transferEncoding;
}

void HttpHeaderBuilder::setLocation(std::string location)
{
	_location = location;
}

void HttpHeaderBuilder::setContentLength(int contentLength)
{
	_contentLength = contentLength;
}

/*
< HTTP/1.1 200 OK
< Server: nginx
< Date: Fri, 07 Jul 2023 08:38:49 GMT
< Content-Type: text/html; charset=utf-8
< Content-Length: 65099
< Connection: keep-alive
< Transfer-Encoding: chunked
*/

/*
std::string	HttpHeaderBuilder::getHeader(void)
{
	std::string			header;
	std::string			httpVersion;
	std::stringstream	contentLength;

	httpVersion = HTTP_VERSION;
	contentLength << _contentLength;
	header = httpVersion + " " + _status + "\r\n";
	if (!_serverName.empty())
		header += "Server: " + _serverName + "\r\n";
	if (!_date.empty())
		header += "Date: " + _date + "\r\n";
	if (!_contentType.empty())
		header += "Content-Type: " + _contentType + "\r\n";
	header += "Content-Length: " + contentLength.str() + "\r\n";
	if (!_connection.empty())
		header += "Connection: " + _connection + "\r\n";
	if (!_transferEncoding.empty())
		header += "Transfer-Encoding: " + _transferEncoding + "\r\n";
	header += "\r\n";
	return (header);
}
*/

std::string	HttpHeaderBuilder::getHeader(void)
{
	std::string			header;
	std::string			httpVersion;
	std::string			server;
	std::stringstream	contentLength;

	httpVersion = HTTP_VERSION;
	server = SERVER_SOFTWARE;
	contentLength << _contentLength;
	header = httpVersion + " " + _status + "\r\n";
	header += "Server: " + server + "\r\n";
	if (!_date.empty())
		header += "Date: " + _date + "\r\n";
	if (!_contentType.empty())
		header += "Content-Type: " + _contentType + "\r\n";
	if (_contentLength)
		header += "Content-Length: " + contentLength.str() + "\r\n";
	if (!_location.empty())
		header += "Location: " + _location + "\r\n";
	if (!_connection.empty())
		header += "Connection: " + _connection + "\r\n";
	if (!_transferEncoding.empty())
		header += "Transfer-Encoding: " + _transferEncoding + "\r\n";
	header += "\r\n";
	return (header);
}