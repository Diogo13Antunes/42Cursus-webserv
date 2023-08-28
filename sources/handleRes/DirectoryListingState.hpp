/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryListingState.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:03:45 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/28 15:25:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

class DirectoryListingState: public IStateRes
{
	private:
		std::map<std::string, std::string>	_getDirContent(std::string directory);
		
		std::string	_getLastModificationDate(std::string path);
		std::string	_createPageHtml(std::string path, std::map<std::string, std::string> dirCont);
		std::string _createHeader(int contLength);
		std::string _resizeName(std::string name);
		bool		_checkDirectoryAccess(Event *event, ServerConfig config);
		std::string _getErrorResponse(void);
		void		_getPreviousRoute(std::string& route);

	public:
		DirectoryListingState(void);
		~DirectoryListingState(void);
		StateResType handle(Event *event, ServerConfig config);
};
