/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaderBuilder.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:34:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/25 15:14:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include "StringUtils.hpp"

class HttpHeaderBuilder
{
	private:
		std::map<std::string, std::string>	_fields;
		std::string	_status;
		std::string	_contentType;
		std::string _date;
		std::string _connection;
		std::string _transferEncoding;
		std::string _location;
		int			_contentLength;

	public:
		HttpHeaderBuilder(void);
		~HttpHeaderBuilder(void);

		void		addNewField(std::string key, std::string value);
		void		setStatus(std::string status);
		void		setContentType(std::string contentType);
		void		setDate(std::string date);
		void		setConnectionClose(void);
		void		setTransferEncoding(std::string transferEncoding);
		void		setContentLength(int contentLength);
		void		setLocation(std::string location);
		std::string	getHeader(void);
};
