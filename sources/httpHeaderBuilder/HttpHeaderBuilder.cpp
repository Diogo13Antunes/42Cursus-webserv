/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaderBuilder.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:34:03 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/25 15:14:42 by dsilveri         ###   ########.fr       */
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

void HttpHeaderBuilder::addNewField(std::string key, std::string value)
{
	_fields.insert(std::make_pair(key, value));
}

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

void HttpHeaderBuilder::setConnectionClose(void)
{
	_connection = "close";
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

std::string	HttpHeaderBuilder::getHeader(void)
{
	std::map<std::string, std::string>::iterator	it;
	std::string										header;
	std::string										httpVersion;
	std::string										server;

	httpVersion = HTTP_VERSION;
	server = SERVER_SOFTWARE;
	header = httpVersion + " " + _status + "\r\n";
	header += "Server: " + server + "\r\n";
	if (!_date.empty())
		header += "Date: " + _date + "\r\n";
	if (!_contentType.empty())
		header += "Content-Type: " + _contentType + "\r\n";
	if (_contentLength)
		header += "Content-Length: " + StringUtils::toString(_contentLength) + "\r\n";
	if (!_location.empty())
		header += "Location: " + _location + "\r\n";
	if (!_connection.empty())
		header += "Connection: " + _connection + "\r\n";
	if (!_transferEncoding.empty())
		header += "Transfer-Encoding: " + _transferEncoding + "\r\n";
	if (!_fields.empty())
	{
		for (it = _fields.begin(); it != _fields.end(); it++)
			header += it->first + ": " + it->second + "\r\n";
	}
	header += "\r\n";
	return (header);
}