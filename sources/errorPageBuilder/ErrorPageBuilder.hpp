/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPageBuilder.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:35:09 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/31 11:06:23 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "map"
#include "string"

class ErrorPageBuilder
{
	private:
		std::string	_reasonPhrase;
		int			_errorCode;

		std::string _getCodeAndPhrase(void);

	public:
		ErrorPageBuilder(void);
		~ErrorPageBuilder(void);

		void		setErrorCode(int errorCode);
		void		setReasonPhrase(std::string reasonPhrase);
		std::string	getErrorPageHtml(void);
		int			getErrorPageSize(void);
};
