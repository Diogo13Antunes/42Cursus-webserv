/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IModule.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:40:02 by dsilveri          #+#    #+#             */
/*   Updated: 2023/05/24 12:00:45 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum
{
    CONNECTIONS_ID,
    EVENTLOOP_ID,
	EVENT_DEMUX
}	ModuleID;

typedef struct s_msg
{
	ModuleID	dst;
	int			fd;
	short		event;
}	t_msg;

class IModule
{
	public:
		virtual ~IModule(void){};
		virtual	ModuleID getId(void) = 0;
		virtual	void handleMessage(t_msg msg) = 0;
};
