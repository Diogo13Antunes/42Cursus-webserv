/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPageBuilder.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:35:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/04 16:28:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorPageBuilder.hpp"

#include <iostream>
#include <sstream>

ErrorPageBuilder::ErrorPageBuilder(void): _errorCode(0)
{
	_reasonPhrase.insert(std::make_pair(404, "Not Found"));
	_reasonPhrase.insert(std::make_pair(400, "Bad Request"));
}

ErrorPageBuilder::ErrorPageBuilder(int errorCode): _errorCode(errorCode)
{
	_reasonPhrase.insert(std::make_pair(404, "Not Found"));
	_reasonPhrase.insert(std::make_pair(400, "Bad Request"));
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

	errorPage = "<!DOCTYPE html>\
				<html lang=\"en\">\
				<head>\
					<meta charset=\"UTF-8\">\
					<title>error</title>\
					<style>\
						h1{\
							text-align: center;\
							font-size: 6vw;\
							margin: auto;\
							padding-bottom: 0px;\
						}\
						h2 {\
							text-align: center;\
							font-size: 3vw;\
							margin-top: 0px;\
							padding-top: 0px;\
							font-weight: normal;\
						}\
					</style>\
				</head>\
				<body>\
					<h1></h1>\
					<h2></h2>\
				</body>\
				</html>";

	idxCode = errorPage.find("<h1>") + 4;
	errorPage.insert(idxCode, this->getErrorCodeToString());
	idxPhrase = errorPage.find("<h2>") + 4;
	errorPage.insert(idxPhrase, this->getReasonPhrase());
	return (errorPage);
}

/*
std::string ErrorPageBuilder::getErrorPageHtml(void)
{
	std::map<int, std::string>::iterator	it;
	std::string								reasonPhrase;
	std::string								errorHtml;
	int										idxErrorCode;
	int										idxErrorPhrase;
	std::stringstream						code;

	it = _reasonPhrase.find(_errorCode);
	if (it == _reasonPhrase.end())
		return (errorHtml);

	errorHtml = "<!DOCTYPE html>\
				<html lang=\"en\">\
				<head>\
					<meta charset=\"UTF-8\">\
					<title>error</title>\
					<style>\
						h1{\
							text-align: center;\
							font-size: 6vw;\
							margin: auto;\
							padding-bottom: 0px;\
						}\
						h2 {\
							text-align: center;\
							font-size: 3vw;\
							margin-top: 0px;\
							padding-top: 0px;\
							font-weight: normal;\
						}\
					</style>\
				</head>\
				<body>\
					<h1></h1>\
					<h2></h2>\
				</body>\
				</html>";

	idxErrorCode = errorHtml.find("<h1>");
	idxErrorPhrase = errorHtml.find("<h2>");
	code << it->first;
	errorHtml.insert(idxErrorCode + 4, code.str());
	errorHtml.insert(idxErrorPhrase + 4, it->second);
	return (errorHtml);
}
*/

int ErrorPageBuilder::getErrorPageSize(void)
{
	return (this->getErrorPageHtml()).size();
}
