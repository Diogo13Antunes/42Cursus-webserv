/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:57:25 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/17 11:58:23 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Signals.hpp"

#include <csignal>
#include <iostream>
#include <cstdlib>

bool Signals::_stopSignal = false;
bool Signals::_childSignal = false;

void Signals::init(void)
{
	signal(SIGINT, Signals::handler);
	signal(SIGTERM, Signals::handler);
	signal(SIGQUIT, Signals::handler);
	signal(SIGCHLD, Signals::handler);
	signal(SIGPIPE, SIG_IGN);
}

void Signals::handler(int signal)
{
	if (signal == SIGINT || signal == SIGTERM || signal == SIGQUIT)
		_stopSignal = true;

	if (signal == SIGCHLD)
		_childSignal = true;
}

bool Signals::isStopSignalTriggered(void)
{
	return (_stopSignal);
}

bool Signals::isChildSignalTriggered(void)
{
	if (_childSignal)
	{
		_childSignal = false;
		return (true);
	}
	return (false);
}
