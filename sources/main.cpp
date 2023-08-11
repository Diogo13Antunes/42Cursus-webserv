/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/11 15:31:47 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configs.hpp"
#include "ConfigsData.hpp"
#include "Server.hpp"

bool	initConfigs(const char *filename, ConfigsData &data)
{
	try
	{
		Configs	cfg(filename);
		data.setupConfigs(cfg.getFileContentVector());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (false);
	}
	return (true);
}

int main(int argc, char **argv)
{
	ConfigsData	confData;

	// Neste caso iniciar default configs
	if (argc != 2)
	{
		std::cout << "Error: No config file" << std::endl;
		return (0);
	}


	if (!initConfigs(argv[1], confData))
		return (-1);
	Server server(confData);
	if (server.init())
		server.start();
	return (0);
}

