/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 09:51:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/11 11:52:47 by dsilveri         ###   ########.fr       */
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

		bool        _initServers(void);
		bool		_initEventLoop(void);
		void		_initConnections(void);
		void		_initEventDemux(void);
		int			_initAndStoreSocketInf(std::string host, std::string port);
		bool		_isServerAlreadyInitialized(std::string host, std::string port);
		void		_addNewServerEndpoint(std::string host, std::string port);
		void		_printIniServerError(std::string host, std::string port);
		void		_printActiveEndpoins(void);
		bool		_isValidPort(std::string port);
		std::string	_getIpAddress(std::string host, std::string port);
		std::string	_getPortFromSocket(int fd);
		
	public:
		Server(void);
		Server(ConfigsData &configs);
		~Server(void);

		bool init(void);
		void start(void);
};
