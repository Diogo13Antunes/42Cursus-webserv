/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:51:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/09 11:26:48 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <map>
#include "ConfigsData.hpp"

class Server
{
	private:
		std::vector<std::string>	_serverEndpoints;
		std::vector<int>			_serverFds;
		ConfigsData					_configs;

		int		_getServerFd(std::string host, std::string port);
		bool	_isServerAlreadyInitialized(std::string host, std::string port);
		void	_addNewServerEndpoint(std::string host, std::string port);
		void	_addNewServerFd(int fd);
		void	_errorStartServerPrint(std::string host, std::string port);


	public:
		Server(void);
		Server(ConfigsData &configs);
		~Server(void);

		void setConfigs(ConfigsData &configs);

		void init(void);
		void start(void);
		void stop(void);
};
