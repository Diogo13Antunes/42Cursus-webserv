/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPageBuilder.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:35:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/31 11:05:22 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorPageBuilder.hpp"
#include "StringUtils.hpp"
#include <iostream>

ErrorPageBuilder::ErrorPageBuilder(void) {}

ErrorPageBuilder::~ErrorPageBuilder(void) {}

void ErrorPageBuilder::setErrorCode(int errorCode)
{
	_errorCode = errorCode;
}

void ErrorPageBuilder::setReasonPhrase(std::string reasonPhrase)
{
	_reasonPhrase = reasonPhrase;
}

std::string ErrorPageBuilder::getErrorPageHtml(void)
{
	std::string	errorPage;
	int			idxCode;
	int			idxPhrase;
	int			idxTitle;

	errorPage = "<!DOCTYPE html>\
				<html>\
				<head>\
					<title></title>\
					<style>\
						h1, h2, p {text-align: center; margin: 0px; padding: 0px;}\
						h1 {font-size: 6vw;}\
						h2 {font-size: 3vw; font-weight: normal;}\
						p  {font-size: 1.5vw;}\
						div {margin-top: 20px; margin-bottom: 20px; margin-left: 80px;\
							margin-right: 80px; border-bottom: 2px solid #888;\
						}\
					</style>\
				</head>\
				<body>\
						<h1></h1><h2></h2><div></div><p>webserv</p>\
				</body>\
				</html>";

	idxTitle = errorPage.find("</title>");
	errorPage.insert(idxTitle, this->_getCodeAndPhrase());
	idxCode = errorPage.find("</h1>");
	errorPage.insert(idxCode, StringUtils::toString(_errorCode));
	idxPhrase = errorPage.find("</h2>");
	errorPage.insert(idxPhrase, _reasonPhrase);
	return (errorPage);
}

std::string	ErrorPageBuilder::_getCodeAndPhrase(void)
{
	std::string statusAndPhrase;

	statusAndPhrase = StringUtils::toString(_errorCode) + " " + _reasonPhrase;
	return (statusAndPhrase);
}

int ErrorPageBuilder::getErrorPageSize(void)
{
	return (this->getErrorPageHtml().size());
}
