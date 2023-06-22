/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:52:16 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/04 13:39:35 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/poll.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>

#include "Terminal.hpp"

#include "MinificatorHTML.hpp"
#include "MinificatorCSS.hpp"
#include "MinificatorJS.hpp"

void	minificateFiles(const std::string filename)
{
	std::string	fileType;
	size_t		index = filename.find_last_of(".") + 1;

	fileType = filename.substr(index, filename.size() - index);
	if (fileType.compare("html") == 0)
	{
		std::string	htmlMinificated;
		htmlMinificated = MinificatorHTML::getMinificatedHTML(filename.c_str());
		std::cout << htmlMinificated << std::endl;
	}
	else if (fileType.compare("css") == 0)
	{
		std::string	cssMinificated;
		cssMinificated = MinificatorCSS::getMinificatedCSS(filename.c_str());
		std::cout << cssMinificated << std::endl;
	}
	else if (fileType.compare("js") == 0)
	{
		std::string	jsMinificated;
		jsMinificated = MinificatorJS::getMinificatedJS(filename.c_str());
		// std::cout << jsMinificated << std::endl;
		std::cout << jsMinificated;
	}
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		Terminal::printErrors("Invalid number of Arguments");
		return (1);
	}

	minificateFiles(av[1]);

	return (0);
}
