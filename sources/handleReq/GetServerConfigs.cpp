/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetServerConfigs.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 08:53:06 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 08:59:50 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GetServerConfigs.hpp"

#include <iostream>

GetServerConfigs::GetServerConfigs(void) {}

GetServerConfigs::~GetServerConfigs(void) {}

StateReqType GetServerConfigs::handle(Event *event, ConfigsData *configsData)
{
	std::cout << "GetServerConfigs" << std::endl;
	exit(0);
}
