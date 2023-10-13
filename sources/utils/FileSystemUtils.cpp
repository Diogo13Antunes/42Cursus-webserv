/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileSystemUtils.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:31:33 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 19:58:25 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileSystemUtils.hpp"
#include <sys/stat.h>
#include <unistd.h>

bool FileSystemUtils::isFolder(std::string path)
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

bool FileSystemUtils::hasReadPermissions(std::string path)
{
	if (access(path.c_str(), R_OK) == 0)
		return (true);
	return (false);
}

bool FileSystemUtils::fileExists(std::string path)
{
	if (access(path.c_str(), F_OK) == 0)
		return (true);
	return (false);
}
