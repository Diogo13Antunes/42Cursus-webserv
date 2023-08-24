/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectoryListing.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:03:41 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/24 09:53:59 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DirectoryListing.hpp"
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include "TimeDate.hpp"
#include "HttpHeaderBuilder.hpp"

#define NAME_MAX_SIZE	48

DirectoryListing::DirectoryListing(void) {}

DirectoryListing::~DirectoryListing(void) {}

StateResType DirectoryListing::handle(Event *event, ServerConfig config)
{
	std::map<std::string, std::string>	dirCont;
	std::string							dir;
	std::string							page;

	dir = event->getResourcePath();
	dirCont = _getDirContent(dir);
	page = _createPageHtml(dir, dirCont);
	event->setRes(_createHeader(page.size()));
	event->updateRes(page);
	return (RESPONSE);
}

std::map<std::string, std::string> DirectoryListing::_getDirContent(std::string directory)
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

std::string DirectoryListing::_getLastModificationDate(std::string path)
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

std::string DirectoryListing::_createPageHtml(std::string path, std::map<std::string, std::string> dirCont)
{
	std::map<std::string, std::string>::iterator	it;
	std::string										page;

	page = "<html><head><title>Index of " + path + "</title></head>";
	page += "<body><h1> Index of " + path + "</h1><hr><pre>";
	for(it = dirCont.begin(); it != dirCont.end(); it++)
	{
		page += "<a href=\"" + it->first +  "\">" + _resizeName(it->first) + "</a>";
		for(int i = it->first.size(); i < NAME_MAX_SIZE; i++)
			page += " ";
		page += " ";
		page += it->second + "\n";
	}
	page += "</pre><hr></body></html>";
	return (page);
}
std::string DirectoryListing::_createHeader(int contLength)
{
	HttpHeaderBuilder	httpHeader;

	httpHeader.setStatus("200 OK");
	httpHeader.setContentLength(contLength);
	httpHeader.setContentType("text/html");
	return (httpHeader.getHeader());
}

std::string DirectoryListing::_resizeName(std::string name)
{
	if (name.size() >= NAME_MAX_SIZE)
	{
		name.erase(NAME_MAX_SIZE - 3);
		name += "...";
	}
	return (name);
}