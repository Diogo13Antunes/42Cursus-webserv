/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetBodyState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:43:43 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/09 16:03:51 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

#define BUFF_SIZE 500000

class GetBodyState: public IStateRes
{
	private:
		char _buff[BUFF_SIZE];
		
		size_t	_getBodyData(std::string& data, std::string fileName, size_t offset);

	public:
		GetBodyState(void);
		GetBodyState(const GetBodyState &src);
		~GetBodyState(void);
		GetBodyState &operator=(const GetBodyState &src);

		StateResType handle(Event *event, ConfigsData configsData);
};
