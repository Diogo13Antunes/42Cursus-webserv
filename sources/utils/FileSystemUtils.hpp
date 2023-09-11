/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileSystemUtils.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:31:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/11 19:58:00 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class FileSystemUtils
{
	public:
		static bool	isFolder(std::string path);
		static bool	hasReadPermissions(std::string path);
		static bool	fileExists(std::string path);
};
