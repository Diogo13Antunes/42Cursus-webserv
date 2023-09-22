/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 11:36:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IState.hpp"

class HeaderProcess: public IState
{
	private:
		ServerConfig*	_getServerConfig(Event *event, ConfigsData *configsData);
		std::string		_getRouteName(ServerConfig& config, std::string reqPath);
		std::string		_getExtesionRoute(ServerConfig& config, std::string reqPath);
		std::string		_getPreviousPath(std::string path);
		std::string		_getRealPath(ServerConfig& config, Event *event, bool isExtesionRoute);
		std::string		_getPathWithIndex(ServerConfig& config, std::string path, std::string route);
		bool			_isChunkedTransfer(Event *event);
		void			_setPathAndRouteInfo(Event *event, ServerConfig& serverConf);
		bool			_cgiPathIsValid(std::string reqPath, std::string realPath);
		
	public:
		HeaderProcess(void);
		~HeaderProcess(void);
		
		StateReqType handle(Event *event, ConfigsData *configsData);
};
