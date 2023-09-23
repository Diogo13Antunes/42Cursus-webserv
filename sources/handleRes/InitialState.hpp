/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:48 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 21:53:05 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"


class InitialState: public IStateRes
{
	private:

		//bool		_isFolder(std::string path);
		std::string _getPreviousPath(std::string reqPath);
		std::string _getRouteName(ServerConfig& config, std::string reqPath);
		std::string	_getRealPath(ServerConfig& config, std::string reqPath, std::string route);
		std::string	_getPathWithIndex(ServerConfig& config, std::string path, std::string route);
		bool		_isMethodImplemented(std::string method);
		bool		_hasForcedRedirection(Event *event, ServerConfig& config);
		bool		_hasConfRedirection(Event *event, ServerConfig& config);
		bool		_isValidMethod(Event *event, ServerConfig& config);
		bool		_isValidFile(Event *event, std::string path);

	public:
		InitialState(void);
		~InitialState(void);

		StateResType handle(Event *event, ServerConfig& config);
};
