/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateResType.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:31:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/22 18:01:30 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum 
{
	CREATE_HEADER,
	CGI_RES_PROCESS,
	GET_BODY,
	REDIRECT,
	DIRECTORY_LISTING,
	RESPONSE,
	RESPONSE_END
}	StateResType;

