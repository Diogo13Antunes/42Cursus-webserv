/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateHeaderState.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:43:02 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/29 15:44:16 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CreateHeaderState.hpp"

#include <iostream>

CreateHeaderState::CreateHeaderState(void)
{
	//Default CreateHeaderState Constructor
}

CreateHeaderState::CreateHeaderState(const CreateHeaderState &src)
{
	//CreateHeaderState Copy Constructor
}

CreateHeaderState::~CreateHeaderState(void)
{
	//Default CreateHeaderState Destructor
}

/*
CreateHeaderState &CreateHeaderState::operator=(const CreateHeaderState &src)
{
	//CreateHeaderState Copy Assignment Operator
}
*/


StateResType CreateHeaderState::handle(Event *event)
{
	std::string fileName;

	std::cout << "CreateHeaderState" << std::endl;

	//event->getReqPath();

	//fileName = _getFileName(event->getReqPath());

	std::cout << "path: " << event->getReqPath() << std::endl;

	return (RESPONSE_END);
}

std::string CreateHeaderState::_getFileName(std::string path)
{
	std::string file;

	if (!path.compare("/"))
		;//filePath = configsData.getConfig("root");
	else
		;//filePath = configsData.getConfig(reqPath);

	return (file);
}

size_t CreateHeaderState::_getBodySize(std::string fileName)
{
	return (0);
}