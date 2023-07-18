/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaderBuilder.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:34:03 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/08 14:45:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpHeaderBuilder.hpp"
#include "TimeDate.hpp"

#include <iostream>
#include <sstream>
#include <ctime>


#define HTTP_VERSION "HTTP/1.1"

HttpHeaderBuilder::HttpHeaderBuilder(void): 
	_contentLength(0), 
	_status("200 OK"),
	_date(TimeDate::getTimeDateIMFfixdateFormat())
{

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

void HttpHeaderBuilder::setConnection(std::string connection)
{
	_connection = connection;
}

void HttpHeaderBuilder::setTransferEncoding(std::string transferEncoding)
{
	_transferEncoding = transferEncoding;
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
