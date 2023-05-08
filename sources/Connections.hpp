/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/08 14:45:48 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include "Connection.hpp"

class Connections
{
	private:
		std::vector<Connection *>	_activeConnects;
		struct pollfd				_fds[1024];

		void removeAllConnections(void);
		void removeConnection(void);

	public:

		Connections(void);
		//Connections(const Connections &src);
		~Connections(void);
		//Connections &operator=(const Connections &src);

		void addNewConnection(int fd, short events);
		struct pollfd *getConnectionsArray(void);
		int getNumConnections(void);

		// for debug only
		void showConnections(void);
};
