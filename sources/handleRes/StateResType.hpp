/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateResType.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:31:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/31 10:14:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum 
{
	INITIAL_STATE,
	ERROR_HANDLING,
	REDIRECTION_HANDLING,
	DIRECTORY_LISTING,
	STATIC_FILE_HANDLING,
	CGI_RES_HANDLING,
	RESPONSE,
	RESPONSE_END
}	StateResType;
