/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateType.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:11:49 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/25 10:18:40 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum 
{
	HEADER_PROCESS,
	BODY_PROCESS,
	REQUEST_END
}	StateType;
