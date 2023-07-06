/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPageBuilder.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:35:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/05 09:16:15 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorPageBuilder.hpp"

#include <iostream>
#include <sstream>

ErrorPageBuilder::ErrorPageBuilder(void): _errorCode(0)
{
	_initErrorCodes();
}

ErrorPageBuilder::ErrorPageBuilder(int errorCode): _errorCode(errorCode)
{
	_initErrorCodes();
}

ErrorPageBuilder::ErrorPageBuilder(const ErrorPageBuilder &src)
{
	//ErrorPageBuilder Copy Constructor
}

ErrorPageBuilder::~ErrorPageBuilder(void)
{
	//Default ErrorPageBuilder Destructor
}

/*
ErrorPageBuilder &ErrorPageBuilder::operator=(const ErrorPageBuilder &src)
{
	//ErrorPageBuilder Copy Assignment Operator
}
*/

int ErrorPageBuilder::getErrorCode(void)
{
	return (_errorCode);
}

void ErrorPageBuilder::setErrorCode(int errorCode)
{
	_errorCode = errorCode;
}

std::string	ErrorPageBuilder::getReasonPhrase(void)
{
	std::map<int, std::string>::iterator	it;
	std::string								reasonPhrase;
	
	it = _reasonPhrase.find(_errorCode);
	if (it != _reasonPhrase.end())
    	reasonPhrase = it->second;
	return (reasonPhrase);
}

std::string ErrorPageBuilder::getErrorCodeToString(void)
{
	std::stringstream errorCode;

	errorCode << _errorCode;
	return (errorCode.str());
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
	errorPage.insert(idxTitle, this->getCodeAndPhrase());
	idxCode = errorPage.find("</h1>");
	errorPage.insert(idxCode, this->getErrorCodeToString());
	idxPhrase = errorPage.find("</h2>");
	errorPage.insert(idxPhrase, this->getReasonPhrase());
	return (errorPage);
}

std::string	ErrorPageBuilder::getCodeAndPhrase(void)
{
	std::string statusAndPhrase;

	statusAndPhrase = this->getErrorCodeToString() + " " + this->getReasonPhrase();
	return (statusAndPhrase);
}

int ErrorPageBuilder::getErrorPageSize(void)
{
	return (this->getErrorPageHtml().size());
}

void ErrorPageBuilder::_initErrorCodes(void)
{
	_reasonPhrase.insert(std::make_pair(404, "Not Found"));
	_reasonPhrase.insert(std::make_pair(400, "Bad Request"));	
}