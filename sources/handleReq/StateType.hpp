/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:11:49 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/23 12:17:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum 
{
	HEADER_GET_DATA,
	HEADER_PROCESS,
	BODY_GET_DATA,
	BODY_PROCESS,
	REQUEST_END
}	StateType;
