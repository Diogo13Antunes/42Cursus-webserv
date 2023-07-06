/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:35:40 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/26 14:06:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum 
{
    READ_EVENT,
    WRITE_EVENT,
    COMPLETE_EVENT
}	EventType;
