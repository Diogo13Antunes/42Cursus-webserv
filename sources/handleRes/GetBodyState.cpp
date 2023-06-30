/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetBodyState.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:43:37 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/30 18:36:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetBodyState.hpp"

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
	std::string data; 
	std::string fileName;

	//std::cout << "GetBodyState" << std::endl;

	fileName = event->getFileName();
	event->updateBytesReadBody(_getBodyData(data, fileName, event->getBytesReadBody()));
	event->updateRes(data);

	// This function will be transfered for response state
	//if (_isBodyFullyRead(event->getBytesReadBody(), event->getBodySize1()))
	//	std::cout << "Readed All Data" << std::endl;
	
	
	//std::cout << event->getRes() << std::endl;
	//std::cout << data << std::endl;

	return (RESPONSE);
}


size_t GetBodyState::_getBodyData(std::string& data, std::string fileName, size_t offset)
{
	int buffSize = 1000000;
    char buff[buffSize];
	size_t read;

    std::ifstream file(fileName.c_str());
    if (!file)
        return (0);
	file.seekg(offset);
	file.read(buff, buffSize);
	read = file.gcount();
	data.assign(buff, read);
	file.close();
	return (read);
}


// This function will be transfered for response state
/*bool GetBodyState::_isBodyFullyRead(size_t bytesRead, size_t bodySize)
{
	if (bytesRead >= bodySize)
		return (true);
	return (false);
}*/
