/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectionHandlingState.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 09:14:49 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/01 08:43:14 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"
#include <map>

class RedirectionHandlingState: public IStateRes
{
	private:
		std::map<int, std::string> _redirCodes;

		std::string _createHeader(ServerConfig& config, int code, std::string resource, int bodySize);
		std::string	_getStatusCode(int code);
		std::string _getLocation(std::string resource, std::string host, std::string port);
		std::string _createBody(int code);

	public:
		RedirectionHandlingState(void);
		~RedirectionHandlingState(void);

		StateResType handle(Event *event, ServerConfig& config);
};
