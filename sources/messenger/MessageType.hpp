/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageType.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:02:38 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/14 15:50:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum 
{
    EVENT_ADD_NEW,
    EVENT_REMOVE,
    EVENT_CHANGE_TO_READ,
    EVENT_CHANGE_TO_WRITE,
    EVENT_READ_TRIGGERED,
    EVENT_WRITE_TRIGGERED,
    CONNECTION_ADD_NEW,
    CONNECTION_REMOVE,
    CONNECTION_PAUSE_TIMER,
    CONNECTION_RESTART_TIMER,
    CONNECTION_RESET_TIMER
} MessageType;