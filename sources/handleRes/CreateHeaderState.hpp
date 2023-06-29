/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateHeaderState.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:43:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/29 14:48:13 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

class CreateHeaderState: public IStateRes
{
	private:
		std::string	_getFileName(std::string path);
		size_t		_getBodySize(std::string fileName);

	public:
		CreateHeaderState(void);
		CreateHeaderState(const CreateHeaderState &src);
		~CreateHeaderState(void);
		CreateHeaderState &operator=(const CreateHeaderState &src);

		StateResType handle(Event *event);
};
