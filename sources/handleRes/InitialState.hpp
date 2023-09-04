/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:48 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/04 16:03:25 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"


class InitialState: public IStateRes
{
	private:
		//bool		_hasRedirection(Event *event, ServerConfig& config);
		bool		_isFolder(std::string path);
		std::string	_getResourceFromURLPath(ServerConfig& config, std::string path);
		std::string _getPreviousRouteResourcePath(ServerConfig& config, std::string path);
		std::string	_getPreviousRoute(std::string path);


		std::string _getPreviousPath(std::string reqPath);
		std::string _getRouteName(ServerConfig& config, std::string reqPath);
		std::string	_getRealPath(ServerConfig& config, std::string reqPath, std::string route);
		std::string	_getPathWithIndex(ServerConfig& config, std::string path, std::string route);
		bool		_isMethodImplemented(std::string method);
		//bool		_hasRedirection(Event *event, ServerConfig& config);
		//bool		_hasRedirection(Event *event, ServerConfig& config, std::string path, std::string route);
		bool		_hasForcedRedirection(Event *event, std::string reqPath, std::string realPath);
		bool		_hasConfRedirection(Event *event, ServerConfig& config, std::string route);

		std::string _getRealPath1(ServerConfig& config, std::string reqPath, std::string route);

	public:
		InitialState(void);
		~InitialState(void);

		StateResType handle(Event *event, ServerConfig& config);
};
