#include "DirectoryListing.hpp"

#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include "TimeDate.hpp"


DirectoryListing::DirectoryListing(void) {}

DirectoryListing::~DirectoryListing(void) {}

StateResType DirectoryListing::handle(Event *event, ServerConfig config)
{
	std::map<std::string, std::string>	dirCont;
	std::string							dir;
	
	std::cout << "DirectoryListing" << std::endl;

	dir = event->getResourcePath();
	dirCont = _getDirContent(dir);

	std::map<std::string, std::string>::iterator it;

	for(it = dirCont.begin(); it != dirCont.end(); it++)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}

	


	exit(0);
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
	{
		std::cout << "Erro abrir directoria" << std::endl;
		return (dirCont);
	}
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
	timeDate = pathInfo.st_mtime;// pathInfo.st_mtime.tv_sec;
	lastMod = TimeDate::FormatLastModification(localtime(&timeDate));
	return (lastMod);
}
