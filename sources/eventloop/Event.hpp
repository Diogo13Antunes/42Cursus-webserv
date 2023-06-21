/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:26 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/21 11:03:32 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "RequestData.hpp"
#include "Configs.hpp"
#include "ConfigsData.hpp"


//#define	NONE			0
#define HEADER_HANDLE	0
#define	HEADER_DONE		1
#define	BODY_HANDLE		2
#define	BODY_DONE		3
 

class Event
{
	private:
		std::string	_reqRaw;
		RequestData	_reqParsed;
		std::string	_res;

		std::string	_headerRaw;

		int			_fd;
		short		_state;
		short		_parseState;


	public:
		Event(void);
		Event(int fd, int state);
		Event(const Event &src);
		~Event(void);
		Event &operator=(const Event &src);

		int			getFd(void);
		short		getState(void);
		std::string	getResponse(void);
		std::string getReqRaw(void);
		std::string getHeaderRaw(void);
		short		getParseState(void);
		size_t		getBodySize(void);


		void		setState(short state);
		void		setResponse(std::string	res);

		void		setResquestHeader(std::string reqLine, std::map<std::string, std::vector<std::string> > reqHeader);
		void		setResquestBody(std::string body);

		void		setParseState(int state);

		void		updateReqRaw(std::string req);

		bool		isBodyComplete(void);

		void		createResponse(ConfigsData configsData);
};
