/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateHeaderState.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:43:02 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/22 17:39:57 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CreateHeaderState.hpp"

#include "ErrorPageBuilder.hpp"
#include "HttpHeaderBuilder.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

CreateHeaderState::CreateHeaderState(void)
{
	//Default CreateHeaderState Constructor
}

CreateHeaderState::~CreateHeaderState(void)
{
	//Default CreateHeaderState Destructor
}


// Não pode existir nenhuma copia a ser feita na ServerConfig config
StateResType CreateHeaderState::handle(Event *event, ServerConfig config)
{
	std::string			fileName;
	std::string			header;
	size_t				fileSize;
	int					errorCode = 0;
	ErrorPageBuilder	errorBuilder;

	ResourceType resourceType;

	int statusCode;


	/*
	struct stat file_info;
	std::cout << "path: " << event->getReqLinePath() << std::endl;
	if (stat(event->getReqLinePath().c_str(), &file_info) == 0) 
	{
		std::cout << "info mode" << file_info.st_mode << std::endl;
    } 
	else
	{		
        perror("Erro ao obter informações do arquivo");
    }
	*/
	



	statusCode = event->getStatusCode();
	if (statusCode)
	{
		errorBuilder.setErrorCode(statusCode);
		event->setBodySize1(errorBuilder.getErrorPageSize());
		_createHeaderDefaultError(header, statusCode, event);
		event->setRes(header);
		event->setResSize(header.size() + fileSize);
		return (GET_BODY);
	}
	if (config.hasRedirection(event->getReqLinePath()))
		return (REDIRECT);

	//verificar se é folder
	std::cout << "caminho real: " << _getResourceFromURLPath(config, event->getReqLinePath(), resourceType) << std::endl;
	std::cout << "resourceType: " << resourceType << std::endl;


	//fileName = _getFileName(event->getReqLinePath(), configsData);
	fileName = _getFileName(event->getReqLinePath(), config);
	if (!event->getCgiScriptResult().empty())
		return (CGI_RES_PROCESS);
	if (_isFileReadable(fileName))
		fileSize = _getFileSize(fileName);
	else
	{
		errorCode = 404;
		event->setErrorCode(errorCode);
		errorBuilder.setErrorCode(errorCode);
		fileSize = errorBuilder.getErrorPageSize();
	}
	event->setBodySize1(fileSize);

	if (errorCode)
		_createHeaderDefaultError(header, errorCode, event);
	else
		_createHeader(header, fileName, event);
	
	event->setFileName(fileName);
	event->setRes(header);
	event->setResSize(header.size() + fileSize);


	return (GET_BODY);
}

std::string CreateHeaderState::_getFileName(std::string reqTarget, ServerConfig &conf)
{
	//ServerConfig	actulServer;
	std::string		fileName;
	std::string		path;

	//actulServer = conf.getServers().at(0);
	fileName = conf.getFilePathByRoute(reqTarget);

	if (fileName.empty())
	{
		path = conf.getGlobalRoutePath();
		fileName = path + "/" + reqTarget;
	}
	return (fileName);
}

bool CreateHeaderState::_isFileReadable(std::string fileName)
{
	std::ifstream file(fileName.c_str());

	if (!file.good())
		return (false);
	file.close();
	return (true);
}

size_t CreateHeaderState::_getFileSize(std::string fileName)
{
	size_t size;
	std::ifstream file(fileName.c_str());

	size = 0;
	if (!file.good())
		return (size);
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.close();	
	return (size);
}

std::string CreateHeaderState::_getFileType(std::string fileName)
{
	std::string type;
	size_t		dotIdx;

	dotIdx = (fileName.find_last_of('.')) + 1;
	if (dotIdx < fileName.size())
		type = fileName.substr(dotIdx, fileName.size());
	return (type);
}

// criar ficheiro default com mime types
std::string CreateHeaderState::_getMimeType(std::string fileExt)
{
	std::string mimeType;

	if (!fileExt.compare("html"))
		mimeType = "text/html";
	else if (!fileExt.compare("css"))
		mimeType = "text/css";
	else if (!fileExt.compare("js"))
		mimeType = "text/javascript";
	else if (!fileExt.compare("png"))
		mimeType = "image/x-png";
	else if (!fileExt.compare("jpg"))
		mimeType = "image/jpeg";
	else if (!fileExt.compare("iso")) // just for test
		mimeType = "text/plain";
	return (mimeType);
}

void CreateHeaderState::_createHeader(std::string &header, std::string fileName, Event *event)
{
	HttpHeaderBuilder	httpHeader;
	std::stringstream	bodySize;

	httpHeader.setStatus("200 OK");
	httpHeader.setContentLength(_getFileSize(fileName));
	httpHeader.setContentType(_getMimeType(_getFileType(fileName)));
	httpHeader.setConnection("keep-alive");
	if (event->isConnectionClose())
		httpHeader.setConnection("close");
	else
		httpHeader.setConnection("keep-alive");
	header = httpHeader.getHeader();
}

void CreateHeaderState::_createHeaderDefaultError(std::string &header, int errorCode, Event *event)
{
	ErrorPageBuilder	errorBuilder(errorCode);
	HttpHeaderBuilder	httpHeader;

	httpHeader.setStatus(errorBuilder.getCodeAndPhrase());
	httpHeader.setContentLength(errorBuilder.getErrorPageSize());
	httpHeader.setContentType(_getMimeType("html"));
	if (event->isConnectionClose())
		httpHeader.setConnection("close");
	else
		httpHeader.setConnection("keep-alive");
	header = httpHeader.getHeader();
}


// Se for um folder sem index então retorna só o folder
// se tiver index então retorna file
// index: tem de ser string vazia se não for configurado
std::string CreateHeaderState::_getResourceFromURLPath(ServerConfig& config, std::string path, ResourceType& type)
{
	std::string rootPath;
	std::string index;
	std::string fullPath;
	std::string fullPathIndex;
	
	rootPath = config.getLocationRootPath(path);
	index = config.getLocationIndex(path);
	fullPath = rootPath + path + "/" + index;
	//IMPORTANTE: se existir alias o alias, o fullPath será:  fullPath = alias + "/" + index;
	if (!_isFolder(fullPath))
	{
		type = FILE_TYPE;
		return (fullPath);
	}
	type = FOLDER_TYPE;
	fullPathIndex = fullPath + "/" + "index.html";
	if (access(fullPathIndex.c_str(), F_OK) == 0)
		return (fullPathIndex);
	return (fullPath);
}

bool CreateHeaderState::_isFolder(std::string path)
{
	struct stat	pathInfo;
	int			err;

	err = stat(path.c_str(), &pathInfo);
	if (!err)
	{
		if (S_ISDIR(pathInfo.st_mode))
			return (true);
	}
	return (false);
}
