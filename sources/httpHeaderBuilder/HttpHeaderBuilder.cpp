/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaderBuilder.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:34:03 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/06 12:25:25 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpHeaderBuilder.hpp"
#include "TimeDate.hpp"

#include <iostream>
#include <sstream>
#include <ctime>

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
	header += "Content-length: " + contentLength.str() + "\r\n";
	if (!_contentType.empty())
		header += "Content-Type: " + _contentType + "\r\n";
	if (!_serverName.empty())
		header += "server: " + _serverName + "\r\n";
	if (!_date.empty())
		header += "date: " + _date + "\r\n";
	header += "\r\n";
	return (header);
}


//Criar class que devolve em imf-fixdate format now and in the date I wanted

/*
std::string HttpHeaderBuilder::_getDateNow(void)
{
	std::string timeStr;
	time_t		now;
	struct tm	*gmt;

	now = time(NULL);
	gmt = gmtime(&now);

	//std::cout << TimeDate::getDayOfWeekToString(gmt->tm_wday) << std::endl;

	std::cout << TimeDate::getTimeDateIMFfixdateFormat() << std::endl;

	//std::cout << now << std::endl;
	std::cout << asctime(gmt) << std::endl;
	return (timeStr);
}
*/

/*
HTTP/1.1 200 OK
Date: Wed, 05 Jul 2023 20:16:07 GMT
Server: Apache
Last-Modified: Wed, 08 Jun 2011 16:38:33 GMT
ETag: "b22017-167-4a535f79db440"
Accept-Ranges: bytes
Content-Length: 359
Keep-Alive: timeout=2, max=135
Connection: Keep-Alive
Content-Type: image/png
*/

/*
HTTP/1.1 404 Not Found
Date: Wed, 05 Jul 2023 20:18:05 GMT
Server: Apache
Vary: Accept-Encoding
Content-Encoding: gzip
Content-Length: 180
Keep-Alive: timeout=2, max=150
Connection: Keep-Alive
Content-Type: text/html; charset=iso-8859-1
*/