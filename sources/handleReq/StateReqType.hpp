/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateReqType.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:11:49 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/04 11:00:24 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum 
{
	HEADER_PROCESS,
	BODY_PROCESS,
	CHUNKED_BODY_PROCESS,
	REQUEST_END
}	StateReqType;
