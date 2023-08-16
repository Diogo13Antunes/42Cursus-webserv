/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/16 10:53:34 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configs.hpp"
#include "ConfigsData.hpp"
#include "Server.hpp"
#include <csignal>

#include "Signals.hpp"

bool	initConfigs(const char *filename, ConfigsData &data)
{
	try
	{
		Configs	cfg(filename);
		data.setupConfigs(cfg.getFileContentVector());
	}
	catch(const std::exception& e)
	{
		// Criar mensagens apropriadas
		std::cerr << e.what() << std::endl;
		return (false);
	}
	return (true);
}

int main(int argc, char **argv)
{
	ConfigsData	confData;
	Server		server;

	Signals::init();
	
	// Neste caso iniciar default configs
	if (argc != 2)
		return (0);

	if (!initConfigs(argv[1], confData))
		return (-1);
	server.setConfigs(&confData);
	if (server.init())
		server.start();
	return (0);
}

