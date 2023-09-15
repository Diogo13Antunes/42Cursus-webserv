/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMessengerClient.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:29:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/15 11:18:31 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMessengerClient.hpp"
#include "Messenger.hpp"

#include <iostream>

AMessengerClient::AMessengerClient(void) {}

AMessengerClient::AMessengerClient(Messenger *messenger):
	_messenger(messenger)
{}

AMessengerClient::~AMessengerClient(void)
{
	if (_messenger)
		_messenger->unregisterClient(clientID);
}

void AMessengerClient::sendMessage(Message msg)
{
	if (_messenger)
		_messenger->sendMessage(msg);
}

void AMessengerClient::setMessenger(Messenger *messenger)
{
	if (messenger)
	{
		_messenger = messenger;
		_messenger->registerClient(this);
		clientID = this->getId();
	}
}
