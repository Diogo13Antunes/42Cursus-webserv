/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryListing.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:03:45 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/24 08:36:36 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

class DirectoryListing: public IStateRes
{
	private:
		std::map<std::string, std::string>	_getDirContent(std::string directory);
		
		std::string	_getLastModificationDate(std::string path);
		std::string	_createPageHtml(std::string path, std::map<std::string, std::string> dirCont);
		std::string _createHeader(int contLength);
		std::string _resizeName(std::string name);

	public:
		DirectoryListing(void);
		~DirectoryListing(void);
		StateResType handle(Event *event, ServerConfig config);
};
