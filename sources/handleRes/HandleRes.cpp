/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:52:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/27 15:26:54 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>

#include "HandleRes.hpp"

HandleRes::HandleRes(void)
{
	//Default HandleRes Constructor
}

HandleRes::HandleRes(const HandleRes &src)
{
	//HandleRes Copy Constructor
}

HandleRes::~HandleRes(void)
{
	//Default HandleRes Destructor
}

/*
HandleRes &HandleRes::operator=(const HandleRes &src)
{
	//HandleRes Copy Assignment Operator
}
*/

/*
void HandleRes::handle(Event *event, ConfigsData confData)
{
	std::string res;

	ssize_t	nWrite;

	event->createResponse(confData);

	res = event->getResponse();


	//nWrite = send(event->getFd(), res.c_str(), res.size(), 0);
	nWrite = send(event->getFd(), res.c_str(), 1000000, 0);
	std::cout <<"size          : " << res.size() << std::endl;
	std::cout <<"Bytes escritos: " << nWrite << std::endl;
}
*/

/*
void HandleRes::handle(Event *event, ConfigsData confData)
{
	std::string res;

	ssize_t	nWrite;

	if (event->getResState() == 0)
		event->createResponse(confData);
	
	
	res = event->getResponse();


	//int buff = 1000000;
	//if (res.size() < buff)
	//	nWrite = send(event->getFd(), res.c_str(), res.size(), 0);
	//else 	
	//	nWrite = send(event->getFd(), res.c_str(), buff, 0);
	
	nWrite = send(event->getFd(), res.c_str(), res.size(), 0);
	if (nWrite == res.size())
		event->setResState(2);
	else
	{
		event->setResState(1);
		if (nWrite)
			event->setResponse(res.substr(nWrite));
	}
	
	std::cout <<"size          : " << res.size() << std::endl;
	std::cout <<"Bytes escritos: " << nWrite << std::endl;
}
*/


void HandleRes::handle(Event *event, ConfigsData confData)
{
	std::string res;
	ssize_t	nWrite;

	if (event->getResState() == 0)
	{
		event->createResponse(confData);
		// preenche vector com a resposa partida
		event->setResVect();
		//event->printVectDebug();
		event->setResState(1);
	}
	
	res = event->getNextRes();

	//std::cout << "res: " << res << std::endl;

	nWrite = send(event->getFd(), res.c_str(), res.size(), 0);
	//event->updateNumWrited(nWrite);
	if (res.size() < nWrite)
		event->updateRes1(res.substr(nWrite));
	else
		event->updateIdx(); // update idx


	// tem de chegar ao último idx e tem de nWrite == res.size()
	if (event->lastIdx() && res.size() == nWrite)
	{
		//std::cout << "TERMINA AQUI" << std::endl;
		event->setResState(2);
	}

	
	//res = event->getResponse();
	
	
	
	//std::cout <<"size          : " << res.size() << std::endl;
	//std::cout <<"Bytes escritos: " << nWrite << std::endl;
}


// usar um estado no evento para verificar o response
// usar um private event
bool HandleRes::isProcessingComplete(Event *event)
{
	if (event->getResState() == 2)
	{
		//std::cout << "isProcessingComplete" << std::endl;
		return (true);
	}
	return (false);
}
