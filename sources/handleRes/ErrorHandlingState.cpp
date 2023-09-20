/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandlingState.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:07:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/20 16:24:54 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorHandlingState.hpp"
#include "HttpHeaderBuilder.hpp"
#include "ErrorPageBuilder.hpp"
#include "StringUtils.hpp"
#include <fstream>

#define ERROR_PAGE_MAX_SIZE	1000
#define ERRO_PAGE_MIME_TYPE	"text/html"

ErrorHandlingState::ErrorHandlingState(void)
{
	_errorCodes.insert(std::make_pair(400, "Bad Request"));
	_errorCodes.insert(std::make_pair(404, "Not Found"));
	_errorCodes.insert(std::make_pair(405, "Method Not Allowed"));
	_errorCodes.insert(std::make_pair(414, "URI Too Long"));
	_errorCodes.insert(std::make_pair(413, "Content Too Large"));
	_errorCodes.insert(std::make_pair(403, "Forbidden"));
	_errorCodes.insert(std::make_pair(408, "Request Timeout"));
	_errorCodes.insert(std::make_pair(501, "Not Implemented"));
	_errorCodes.insert(std::make_pair(500, "Internal Server Error"));
	_errorCodes.insert(std::make_pair(504, "Gateway Timeout"));
}

ErrorHandlingState::~ErrorHandlingState(void) {}

StateResType ErrorHandlingState::handle(Event *event, ServerConfig& config)
{
	int			errorCode;
	std::string	pagePath;
	std::string header;
	std::string pageHtml;
	std::string res;

	errorCode = event->getStatusCode();
	if (errorCode != 404)
		event->setConnectionClose();
	if (event->getServerConfing())
		pagePath = config.getErrorPagePath(errorCode);
	if (!pagePath.empty())
		_getPageFromFile(pagePath, pageHtml);
	if (pageHtml.empty())
		_getDefaultPage(errorCode, pageHtml);
	_getHeader(event, pageHtml.size(), header);
	res = header + pageHtml;
	event->setRes(res);
	event->setResSize(res.size());
	return (RESPONSE);
}

void ErrorHandlingState::_getPageFromFile(std::string path, std::string& page)
{
	size_t	bytesRead;
	char	buff[ERROR_PAGE_MAX_SIZE];

    std::ifstream file(path.c_str());
    if (!file)
        return ;
	file.read(buff, ERROR_PAGE_MAX_SIZE);
	bytesRead = file.gcount();
	page.assign(buff, bytesRead);
	file.close();
}

void ErrorHandlingState::_getDefaultPage(int errorCode, std::string& page)
{
	std::map<int, std::string>::iterator	it;
	ErrorPageBuilder						errorPageBuilder;

	errorPageBuilder.setErrorCode(errorCode);
	it = _errorCodes.find(errorCode);
	if (it != _errorCodes.end())
		errorPageBuilder.setReasonPhrase(it->second);
	else
		errorPageBuilder.setReasonPhrase("Error");
	page.assign(errorPageBuilder.getErrorPageHtml());
}

void ErrorHandlingState::_getHeader(Event *event, size_t pageSize, std::string& header)
{
	HttpHeaderBuilder	headerBuilder;
	int					errorCode;
	std::string			status;

	errorCode = event->getStatusCode();
	status = StringUtils::toString(errorCode) + " " +_getErrorMessage(errorCode);
	headerBuilder.setStatus(status);
	headerBuilder.setContentType(ERRO_PAGE_MIME_TYPE);
	headerBuilder.setContentLength(pageSize);
	if (event->isConnectionClose())
		headerBuilder.setConnectionClose();
	header.assign(headerBuilder.getHeader());
}

std::string ErrorHandlingState::_getErrorMessage(int errorCode)
{
	std::map<int, std::string>::iterator	it;

	it = _errorCodes.find(errorCode);
	if (it != _errorCodes.end())
		return (it->second);
	return (std::string());
}
