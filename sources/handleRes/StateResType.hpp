/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StateResType.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:31:44 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/12 15:25:37 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum 
{
	CREATE_HEADER,
	CGI_RES_PROCESS,
	GET_BODY,
	RESPONSE,
	RESPONSE_END
}	StateResType;

