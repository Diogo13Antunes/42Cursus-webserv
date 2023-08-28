/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitialState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:51:48 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/28 11:47:23 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"


class InitialState: public IStateRes
{
	private:
		bool		_hasRedirection(Event *event, ServerConfig config);
		bool		_isFolder(std::string path);
		std::string	_getResourceFromURLPath(ServerConfig& config, std::string path);

	public:
		InitialState(void);
		~InitialState(void);

		StateResType handle(Event *event, ServerConfig config);
};
