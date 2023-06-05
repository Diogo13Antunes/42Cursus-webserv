/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMessengerClient.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:29:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/01 10:33:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMessengerClient.hpp"
#include "Messenger.hpp"

#include <iostream>

AMessengerClient::AMessengerClient(void) {}

AMessengerClient::AMessengerClient(Messenger *messenger):
	_messenger(messenger)
{}

AMessengerClient::AMessengerClient(const AMessengerClient &src) {}

AMessengerClient::~AMessengerClient(void)
{
	if (_messenger)
		_messenger->unregisterClient(clientID);
}

/*
AMessengerClient &AMessengerClient::operator=(const AMessengerClient &src)
{
	//AMessegerClient Copy Assignment Operator
}
*/

void AMessengerClient::sendMessage(Message *msg)
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
