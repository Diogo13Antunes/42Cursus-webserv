/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateHeaderState.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:43:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/22 17:34:59 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

typedef enum {
    FILE_TYPE,
    FOLDER_TYPE,
    UNKNOWN_TYPE
}	ResourceType;

class CreateHeaderState: public IStateRes
{
	private:
		std::string	_getFileName(std::string reqTarget, ConfigsData &conf);
		size_t		_getFileSize(std::string fileName);
		bool		_isFileReadable(std::string fileName);
		void		_createHeader(std::string &header, std::string fileName, Event *event);
		void		_createHeaderDefaultError(std::string &header, int errorCode, Event *event);
		std::string	_getFileType(std::string fileName);
		std::string _getMimeType(std::string fileExt);

		std::string _getFileName(std::string reqTarget, ServerConfig &conf);

		std::string _getResourceFromURLPath(ServerConfig& config, std::string path, ResourceType& type);
		bool _isFolder(std::string path);

	public:
		CreateHeaderState(void);
		~CreateHeaderState(void);

		StateResType handle(Event *event, ServerConfig config);
};
