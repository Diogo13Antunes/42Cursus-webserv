/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:21 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/05 14:31:45 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

Connection::Connection(int fd, short events)
{
	this->_fd.fd = fd;
	this->_fd.events = events;
	this->_fd.revents = 0;

	std::cout << "new Conection " << this->_fd.fd << std::endl;
}

/*
Connection::Connection(const Connection &src)
{

}
*/

Connection::~Connection(void)
{
	std::cout << "close conection " << this->_fd.fd << std::endl;
	close(this->_fd.fd);
}

/*
Connection &Connection::operator=(const Connection &src)
{

}
*/