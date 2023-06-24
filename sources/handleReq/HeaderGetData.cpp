/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderGetData.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:50:06 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/24 14:40:05 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "HeaderGetData.hpp"

HeaderGetData::HeaderGetData(void)
{
	//Default HeaderGetData Constructor
}

HeaderGetData::HeaderGetData(const HeaderGetData &src)
{
	//HeaderGetData Copy Constructor
}

HeaderGetData::~HeaderGetData(void)
{
	//Default HeaderGetData Destructor
}

/*
HeaderGetData &HeaderGetData::operator=(const HeaderGetData &src)
{
	//HeaderGetData Copy Assignment Operator
}
*/

StateType HeaderGetData::handle(Event *event)
{
	const std::string	req = event->getReqRaw1();
	size_t				headerEndIdx;

	std::cout << "HeaderGetData" << std::endl;
	headerEndIdx = req.find("\r\n\r\n");
	if (headerEndIdx != std::string::npos)
	{
		event->setHeaderRaw(req.substr(0, headerEndIdx + 4));
		return (HEADER_PROCESS);
	}
    return (HEADER_GET_DATA);
}