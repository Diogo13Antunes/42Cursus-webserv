/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:51:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/09 15:46:19 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include <map>

#include "ConfigsData.hpp"
#include "Messenger.hpp"
#include "EventLoop.hpp"
#include "Connections.hpp"

class Server
{
	private:
		std::vector<std::string>	_serverEndpoints;
		std::vector<int>			_serverFds;
		ConfigsData					_configs;
		Messenger					_messenger;
		EventLoop					_eventLoop;
		Connections					_connections;
		//EventDemux					eventDemux(server_fd, address, (socklen_t) addrlen);

		int			_getServerFd(std::string host, std::string port);
		bool		_isServerAlreadyInitialized(std::string host, std::string port);
		void		_addNewServerEndpoint(std::string host, std::string port);
		void		_addNewServerFd(int fd);
		void		_errorStartServerPrint(std::string host, std::string port);
		void		_printActiveEndpoins(void);
		std::string	_getIpAddress(std::string host, std::string port);
		bool		_initEventLoop(void);
		bool		_initConnections(void);
		bool		_initEventDemux(void);

	public:
		Server(void);
		Server(ConfigsData &configs);
		~Server(void);

		void setConfigs(ConfigsData &configs);

		bool init(void);
		void start(void);
		void stop(void);
};
