/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateResType.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:31:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/29 11:34:13 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum 
{
	CREATE_HEADER,
	GET_BODY,
	RESPONSE,
	WAIT_NEW_EVENT,
	RESPONSE_END
}	StateResType;

