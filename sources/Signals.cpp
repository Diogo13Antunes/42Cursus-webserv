/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:57:25 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/16 11:08:51 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Signals.hpp"

#include <csignal>
#include <iostream>
#include <cstdlib>

bool Signals::_stopSignal = false;


// SIGCHLD
// Fazer verificação se algum cgi terminou em vez de iterar sempre a lista de CGI, 
// apenas itera se existir um seinal de termino de CGI.
void Signals::init(void)
{
	signal(SIGINT, Signals::handler);
	signal(SIGTERM, Signals::handler);
	signal(SIGQUIT, Signals::handler);
	signal(SIGPIPE, SIG_IGN);
}

void Signals::handler(int signal)
{
	//std::cout << "Signal: " << signal << std::endl;
	if (signal == SIGINT || signal == SIGTERM || signal == SIGQUIT)
		_stopSignal = true;
}

bool Signals::isStopSignalTriggered(void)
{
	return (_stopSignal);
}
