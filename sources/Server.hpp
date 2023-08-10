/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:51:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/10 16:30:43 by dsilveri         ###   ########.fr       */
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
#include "EventDemux.hpp"

class Server
{
	private:
		std::vector<std::string>			_serverEndpoints;
		std::map<int, struct sockaddr_in>	_serversInfo;
		ConfigsData							_configs;
		Messenger							_messenger;
		EventLoop							_eventLoop;
		Connections							_connections;
		EventDemux							_eventDemux;

		bool		_initAndStoreSocketInf(std::string host, std::string port);
		bool		_isServerAlreadyInitialized(std::string host, std::string port);
		void		_addNewServerEndpoint(std::string host, std::string port);
		void		_errorStartServerPrint(std::string host, std::string port);
		void		_printActiveEndpoins(void);
		std::string	_getIpAddress(std::string host, std::string port);
		bool        _initServers(void);
		bool		_initEventLoop(void);
		bool		_initConnections(void);
		bool		_initEventDemux(void);

	public:
		Server(void);
		Server(ConfigsData &configs);
		~Server(void);

		bool init(void);
		void start(void);
};
