/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderGetData.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:50:02 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/23 19:18:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IState.hpp"

class HeaderGetData: public IState 
{
	public:
		HeaderGetData(void);
		HeaderGetData(const HeaderGetData &src);
		~HeaderGetData(void);
		HeaderGetData &operator=(const HeaderGetData &src);

		StateType handle(Event *event);
};
