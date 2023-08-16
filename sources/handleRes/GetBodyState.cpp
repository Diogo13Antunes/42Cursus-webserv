/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetBodyState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:43:37 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/16 16:49:57 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetBodyState.hpp"

#include "ErrorPageBuilder.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

GetBodyState::GetBodyState(void)
{
	//Default GetBodyState Constructor
}

GetBodyState::GetBodyState(const GetBodyState &src)
{
	//GetBodyState Copy Constructor
}

GetBodyState::~GetBodyState(void)
{
	//Default GetBodyState Destructor
}

/*
GetBodyState &GetBodyState::operator=(const GetBodyState &src)
{
	//GetBodyState Copy Assignment Operator
}
*/

StateResType GetBodyState::handle(Event *event, ConfigsData configsData)
{
	std::string			data; 
	std::string			fileName;
	ErrorPageBuilder	errorBuilder;

	if (event->getStatusCode())
	{
		errorBuilder.setErrorCode(event->getStatusCode());
		data = errorBuilder.getErrorPageHtml();
	}
	else if (event->getErrorCode())
	{
		errorBuilder.setErrorCode(event->getErrorCode());
		data = errorBuilder.getErrorPageHtml();
	}
	else if (!event->getCgiBodyRes().empty())
	{
		if (event->getTotalBytesSend() == 0)
			data = event->getCgiBodyRes();
	}
	else
	{
		fileName = event->getFileName();
		event->updateBytesReadBody(_getBodyData(data, fileName, event->getBytesReadBody()));
	}
	event->updateRes(data);
	return (RESPONSE);
}

size_t GetBodyState::_getBodyData(std::string& data, std::string fileName, size_t offset)
{
	size_t read;

    std::ifstream file(fileName.c_str());
    if (!file)
        return (0);
	file.seekg(offset);
	file.read(_buff, BUFF_SIZE);
	read = file.gcount();
	data.assign(_buff, read);
	file.close();
	return (read);
}
