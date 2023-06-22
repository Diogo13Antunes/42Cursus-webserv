/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IState.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:17:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/22 16:22:57 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class IState
{
    public:
    	virtual ~IState(void) {};

		virtual IState* handle(void) = 0;
};