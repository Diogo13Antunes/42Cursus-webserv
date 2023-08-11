/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 17:10:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/11 17:38:00 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class SocketUtils
{
	public:
		static void			getHostAndPort(int fd, std::string& hostIP, std::string& port);
		static std::string	getHostIP(int fd);
		static std::string	getPort(int fd);
		static std::string	getIpAddress(std::string host, std::string port);
};
