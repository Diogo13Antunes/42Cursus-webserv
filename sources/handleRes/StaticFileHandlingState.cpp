/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StaticFileHandlingState.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:53:06 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/30 19:55:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StaticFileHandlingState.hpp"
#include "HttpHeaderBuilder.hpp"
#include <iostream>

StaticFileHandlingState::StaticFileHandlingState(void) {}

StaticFileHandlingState::~StaticFileHandlingState(void) {}

StateResType StaticFileHandlingState::handle(Event *event, ServerConfig& config)
{
	std::string	filePath;
	std::string	data;
	std::string	header;
	std::string	mimeType;
	size_t		fileSize;
	size_t		offset;
	
	filePath = event->getResourcePath();
	mimeType = _getMimeTypes(config, filePath);
	if (!event->getFileSize())
	{
		fileSize = _getFileSize(filePath);
		_createHeader(event->isConnectionClose(), fileSize, mimeType, header);
		event->setFileSize(_getFileSize(filePath));
		event->setRes(header);
		event->setResSize(header.size() + fileSize);
	}
	offset = event->getFileNumBytesRead();
	if (offset == event->getFileSize())
		return (RESPONSE);
	event->updateFileNumBytesRead(_getFileContent(data, filePath, offset));
	event->updateRes(data);
	return (RESPONSE);
}

size_t StaticFileHandlingState::_getFileSize(std::string filePath)
{
	size_t			size;
	std::ifstream	file(filePath.c_str());

	size = 0;
	if (!file.good())
		return (size);
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.close();	
	return (size);
}

size_t StaticFileHandlingState::_getFileContent(std::string& data, std::string filePath, size_t offset)
{
	size_t	bytesRead;

    std::ifstream file(filePath.c_str());
    if (!file)
        return (0);
	file.seekg(offset);
	file.read(_buff, FILE_BUFF_SIZE);
	bytesRead = file.gcount();
	data.assign(_buff, bytesRead);
	file.close();
	return (bytesRead);
}

void StaticFileHandlingState::_createHeader(bool isCloseConnect, size_t fileSize, std::string mimeType, std::string& header)
{
	HttpHeaderBuilder	httpHeader;

	httpHeader.setContentLength(fileSize);
	httpHeader.setContentType(mimeType);
	if (isCloseConnect)
		httpHeader.setConnectionClose();
	header.assign(httpHeader.getHeader());
}

std::string StaticFileHandlingState::_getFileType(std::string filePath)
{
	std::string	type;
	size_t		dotIdx;

	dotIdx = (filePath.find_last_of('.')) + 1;
	if (dotIdx < filePath.size())
		type = filePath.substr(dotIdx, filePath.size());
	return (type);
}

std::string StaticFileHandlingState::_getInternalMimeTypes(std::string fileType)
{
	std::string	mimeType;

	if (!fileType.compare("html"))
		mimeType = "text/html";
	else if (!fileType.compare("css"))
		mimeType = "text/css";
	else if (!fileType.compare("js"))
		mimeType = "text/javascript";
	else if (!fileType.compare("png"))
		mimeType = "image/x-png";
	else if (!fileType.compare("jpg"))
		mimeType = "image/jpeg";
	else
		mimeType = "text/plain";
	return (mimeType);
}

std::string StaticFileHandlingState::_getMimeTypes(ServerConfig& config, std::string filePath)
{
	std::string	fileType;
	std::string	mimeType;

	fileType = _getFileType(filePath);
	mimeType = config.getMimeTypeByFileType(fileType);
	if (mimeType.empty())
		mimeType = _getInternalMimeTypes(fileType);
	return (mimeType);
}

