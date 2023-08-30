/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticFileHandlingState.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:53:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/30 07:58:03 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

#define FILE_BUFF_SIZE 500000

class StaticFileHandlingState: public IStateRes
{
	private:
		char _buff[FILE_BUFF_SIZE];

		size_t		_getFileSize(std::string filePath);
		size_t		_getFileContent(std::string& data, std::string filePath, size_t offset);
		void		_createHeader(bool isCloseConnect, size_t fileSize, std::string mimeType, std::string& header);
		std::string _getFileType(std::string filePath);
		std::string	_getInternalMimeTypes(std::string fileType);
		std::string _getMimeTypes(ServerConfig config, std::string filePath);

	public:
		StaticFileHandlingState(void);
		~StaticFileHandlingState(void);

		StateResType handle(Event *event, ServerConfig config);
};
