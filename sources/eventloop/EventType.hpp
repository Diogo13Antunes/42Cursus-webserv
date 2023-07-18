/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:35:40 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/17 09:23:19 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/*
typedef enum 
{
    READ_EVENT,
    WRITE_EVENT,
    CGI_EVENT,
    CGI_EXECUTION,
    COMPLETE_EVENT
}	EventType;
*/

typedef enum 
{
    READ_EVENT,
    READ_EVENT_COMPLETE,
    WRITE_EVENT,
    WRITE_EVENT_COMPLETE,
    CGI_EVENT,
    CGI_EXECUTION, // Não está a ser usado
    CGI_EVENT_COMPLETE,
    CLOSED_EVENT,
}	EventType;
