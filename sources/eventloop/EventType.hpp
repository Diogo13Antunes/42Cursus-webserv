/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EventType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:35:40 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/15 15:58:01 by dsilveri         ###   ########.fr       */
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


	READ_SOCKET,
	READ_CGI,
	WRITE_CGI,
	CLOSE_EVENT,
	TYPE_TRANSITION
}	EventType;

// No final deve ficar
/*
typedef enum 
{
	READ_SOCKET,
	WRITE_SOCKET,
	READ_CGI,
	WRITE_CGI,
	TYPE_TRANSITION
}	EventType;
*/