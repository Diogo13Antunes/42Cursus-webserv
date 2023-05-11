/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/04 13:39:35 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/poll.h>
#include <errno.h>

#include <fstream>

#include "Configs.hpp"
#include "ConfigsData.hpp"

bool	initConfigs(const char *filename, ConfigsData &data)
{
	std::string	key, value;

	try
	{
		Configs	cfg(filename);
		while (cfg.getNextConfig(key, value))
			data.addNewConfigs(key, value);
		std::cout << "listen:   " << data.getListen() << std::endl;
		std::cout << "ServName: " << data.getServerName() << std::endl;
		std::cout << "Root:     " << data.getRoot() << std::endl;
		std::cout << "Index:    " << data.getIndex() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (false);
	}
	return (true);
}

int main(int ac, char **av)
{
	ConfigsData	data;

	if (ac != 2)
	{
		Terminal::printErrors("Invalid number of Arguments");
		return (1);
	}

	if (!initConfigs(av[1], data))
		return (1);

	return (0);
}
