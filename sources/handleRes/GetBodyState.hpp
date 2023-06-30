/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetBodyState.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:43:43 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/30 16:47:31 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

class GetBodyState: public IStateRes
{
	private:
		size_t	_getBodyData(std::string& data, std::string fileName, size_t offset);
		//bool	_isBodyFullyRead(size_t bytesRead, size_t bodySize);

	public:
		GetBodyState(void);
		GetBodyState(const GetBodyState &src);
		~GetBodyState(void);
		GetBodyState &operator=(const GetBodyState &src);

		StateResType handle(Event *event, ConfigsData configsData);
};
