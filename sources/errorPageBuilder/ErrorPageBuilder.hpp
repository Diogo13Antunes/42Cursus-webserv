/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPageBuilder.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:35:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/04 15:29:01 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map"
#include "string"

class ErrorPageBuilder
{
	private:
		std::map<int, std::string> _reasonPhrase;
		int						   _errorCode;

	public:
		ErrorPageBuilder(void);
		ErrorPageBuilder(int errorCode);
		ErrorPageBuilder(const ErrorPageBuilder &src);
		~ErrorPageBuilder(void);
		ErrorPageBuilder &operator=(const ErrorPageBuilder &src);

		int		getErrorCode(void);
		void	setErrorCode(int errorCode);

		std::string	getReasonPhrase(void);
		std::string	getErrorCodeToString(void);
		std::string	getErrorPageHtml(void);
		int			getErrorPageSize(void);
};
