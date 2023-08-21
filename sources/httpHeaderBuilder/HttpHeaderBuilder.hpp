/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeaderBuilder.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:34:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/18 16:27:56 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class HttpHeaderBuilder
{
	private:
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

		void		setStatus(std::string status);
		void		setContentType(std::string contentType);
		void		setDate(std::string date);
		void		setConnection(std::string connection);
		void		setTransferEncoding(std::string transferEncoding);
		void		setContentLength(int contentLength);
		void		setLocation(std::string location);
		std::string	getHeader(void);
};
