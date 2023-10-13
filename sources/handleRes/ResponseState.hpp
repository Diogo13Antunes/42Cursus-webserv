/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseState.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:15:11 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/30 19:51:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

class ResponseState: public IStateRes
{
	private:
		bool	_isResponseFullySend(size_t bytesRead, size_t bodySize);

	public:
		ResponseState(void);
		ResponseState(const ResponseState &src);
		~ResponseState(void);
		ResponseState &operator=(const ResponseState &src);

		StateResType handle(Event *event, ServerConfig& config);
};
