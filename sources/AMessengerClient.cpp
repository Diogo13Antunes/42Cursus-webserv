/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMessengerClient.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:29:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/28 14:29:01 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMessengerClient.hpp"
#include "Messenger.hpp"

#include <iostream>

AMessengerClient::AMessengerClient(void)
{
	//Default AMessegerClient Constructor
}

AMessengerClient::AMessengerClient(Messenger *messenger):
	_messenger(messenger)
{}

AMessengerClient::AMessengerClient(const AMessengerClient &src)
{
	//AMessegerClient Copy Constructor
}

AMessengerClient::~AMessengerClient(void)
{
	if (_messenger)
		_messenger->unregisterClient(clientID);

	//Default AMessegerClient Destructor
}

/*
AMessengerClient &AMessengerClient::operator=(const AMessengerClient &src)
{
	//AMessegerClient Copy Assignment Operator
}
*/

void AMessengerClient::sendMessage(t_msg msg)
{
	if (_messenger)
		_messenger->sendMessage(msg);
}

void AMessengerClient::setMessenger(Messenger *messenger)
{
	_messenger = messenger;
	if (_messenger)
	{
		_messenger->registerClient(this);
		clientID = this->getId();
	}
}