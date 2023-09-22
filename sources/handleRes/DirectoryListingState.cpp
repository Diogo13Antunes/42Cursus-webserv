/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryListingState.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:03:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/22 15:54:02 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DirectoryListingState.hpp"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include "TimeDate.hpp"
#include "HttpHeaderBuilder.hpp"
#include "configs.hpp"
#include "FileSystemUtils.hpp"

#define NAME_MAX_SIZE	48

DirectoryListingState::DirectoryListingState(void) {}

DirectoryListingState::~DirectoryListingState(void) {}

StateResType DirectoryListingState::handle(Event *event, ServerConfig& config)
{
	std::map<std::string, std::string>	dirCont;
	std::string							dir;
	std::string							page;
	std::string							header;
	std::string							res;

	dir = event->getResourcePath();
	dirCont = _getDirContent(dir);
	page = _createPageHtml(dir, dirCont);
	header = _createHeader(page.size());
	res = header + page;
	event->setRes(res);
	event->setResSize(res.size());
	return (RESPONSE);
}

std::map<std::string, std::string> DirectoryListingState::_getDirContent(std::string directory)
{
	std::map<std::string, std::string>	dirCont;
	struct dirent						*entry;
	DIR									*dir;
	std::string							name;
	std::string							lastMod;

	dir = opendir(directory.c_str());
	if (!dir)
		return (dirCont);
	while (true)
	{
		entry = readdir(dir);
		if (!entry)
			break;
		name = entry->d_name;
		lastMod = _getLastModificationDate(directory + "/" + name);
		dirCont.insert(std::make_pair(name, lastMod));
	}
	closedir(dir);
	return (dirCont);
}

std::string DirectoryListingState::_getLastModificationDate(std::string path)
{
	struct stat	pathInfo;
	time_t		timeDate;
	std::string	lastMod;
	int			err;

	err = stat(path.c_str(), &pathInfo);
	if (err)
		return (std::string());
	timeDate = pathInfo.st_mtime;
	lastMod = TimeDate::FormatLastModification(localtime(&timeDate));
	return (lastMod);
}

std::string DirectoryListingState::_createPageHtml(std::string path, std::map<std::string, std::string> dirCont)
{
	std::map<std::string, std::string>::iterator	it;
	std::string										page;

	_sanitizePath(path);
	page = "<html><head><title>Index of " + path + "</title></head>";
	page += "<body><h1> Index of " + path + "</h1><hr><pre>";
	for(it = dirCont.begin(); it != dirCont.end(); it++)
	{
		if (FileSystemUtils::isFolder(path + it->first))
			page += "<a href=\"" + it->first + "/" +  "\">" + _resizeName(it->first) + "</a>";
		else
			page += "<a href=\"" + it->first + "\">" + _resizeName(it->first) + "</a>";
		for(int i = it->first.size(); i < NAME_MAX_SIZE; i++)
			page += " ";
		page += " ";
		page += it->second + "\n";
	}
	page += "</pre><hr></body></html>";
	return (page);
}

std::string DirectoryListingState::_createHeader(int contLength)
{
	HttpHeaderBuilder	httpHeader;

	httpHeader.setStatus("200 OK");
	httpHeader.setContentLength(contLength);
	httpHeader.setContentType("text/html");
	return (httpHeader.getHeader());
}

std::string DirectoryListingState::_resizeName(std::string name)
{
	if (name.size() >= NAME_MAX_SIZE)
	{
		name.erase(NAME_MAX_SIZE - 3);
		name += "...";
	}
	return (name);
}

void DirectoryListingState::_getPreviousRoute(std::string& route)
{
	size_t idx;

	if (route.size() == 1)
		return ;
	if (route.at(route.size() - 1) == '/')
		route.erase(route.size() - 1);
	idx = route.find_last_of("/");
	if (idx != route.npos && idx > 0)
		route.erase(idx);
	else if (idx != route.npos)
		route.erase(idx + 1);
}

void DirectoryListingState::_sanitizePath(std::string& path)
{
	size_t idx;

	while (true)
	{
		idx = path.find("//");
		if (idx == path.npos)
			break ;
		else
			path.erase(idx, 1);
	}
}
