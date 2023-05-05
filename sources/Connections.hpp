/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:51:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/05 17:43:50 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include "Connection.hpp"

class Connections
{
	private:
		std::vector<Connection *> activeConnects;

		void removeAllConnections(void);


	public:

		//std::vector<Connection *> connect;

		Connections(void);
		//Connections(const Connections &src);
		~Connections(void);
		//Connections &operator=(const Connections &src);

		void addConnection(int fd, short events);
		void removeConnection(void);

		// for debug only
		void showConnections(void);
};
