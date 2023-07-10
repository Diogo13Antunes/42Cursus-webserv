/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaderBuilder.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:34:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/07 11:18:57 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class HttpHeaderBuilder
{
	private:
		std::string	_status;
		std::string	_contentType;
		std::string _serverName;
		std::string _date;
		std::string _connection;
		std::string _transferEncoding;
		int			_contentLength;

		//std::string _getDateNow(void);

	public:
		HttpHeaderBuilder(void);
		HttpHeaderBuilder(const HttpHeaderBuilder &src);
		~HttpHeaderBuilder(void);
		HttpHeaderBuilder &operator=(const HttpHeaderBuilder &src);

		void		setStatus(std::string status);
		void		setContentType(std::string contentType);
		void		setServerName(std::string serverName);
		void		setDate(std::string date);
		void		setConnection(std::string connection);
		void		setTransferEncoding(std::string transferEncoding);
		void		setContentLength(int contentLength);
		std::string	getHeader(void);
};
