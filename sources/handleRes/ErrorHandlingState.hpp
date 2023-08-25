/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorHandlingState.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:07:25 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/25 14:46:44 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"
#include <map>

class ErrorHandlingState: public IStateRes
{
	private:
		std::map<int, std::string> _errorCodes;

		void		_getPageFromFile(std::string path, std::string& data);
		void		_getDefaultPage(int errorCode, std::string& data);
		void		_getHeader(Event *event, size_t pageSize, std::string& header);
		std::string	_getErrorMessage(int errorCode);

	public:
		ErrorHandlingState(void);
		~ErrorHandlingState(void);

		StateResType handle(Event *event, ServerConfig config);
};
