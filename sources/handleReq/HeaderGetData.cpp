/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderGetData.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:50:06 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/23 12:57:36 by dsilveri         ###   ########.fr       */
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

StateType HeaderGetData::handle(void)
{
	std::cout << "HeaderGetData" << std::endl;
    return (HEADER_PROCESS);
}