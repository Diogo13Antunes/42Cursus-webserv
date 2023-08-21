/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectionHandler.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:14:49 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/19 11:44:00 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"
#include <map>

class RedirectionHandler: public IStateRes
{
	private:
		std::map<int, std::string> _redirCodes;

		std::string _createHeader(ServerConfig config, int code, std::string resource);
		std::string	_getStatusCode(int code);
		std::string _getLocation(std::string resource, std::string host, std::string port);

	public:
		RedirectionHandler(void);
		~RedirectionHandler(void);

		StateResType handle(Event *event, ServerConfig config);
};
