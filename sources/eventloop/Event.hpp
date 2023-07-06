/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:26 by dsilveri          #+#    #+#             */
/*   Updated: 2023/07/06 15:23:05 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "RequestData.hpp"
#include "Configs.hpp"
#include "ConfigsData.hpp"
#include "StateType.hpp"
#include "StateResType.hpp"


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
		std::string _bodyRaw;

		int			_fd;
		short		_state;
		short		_parseState;

		StateType	_reqState;


		int			_resState;

		std::vector<std::string> _resVect;
		ssize_t _numWrited;
		int _idx;

		// for andleRes
		std::string		_fileName;
		size_t			_bodySize;   // talvez não seja necessário devido ao _resSize
		size_t			_bytesReadBody;
		size_t			_resSize;
		size_t			_totalBytesSend;
		StateResType	_resState1;
		int				_errorCode;
		


	public:
		Event(void);
		Event(int fd, int state);
		Event(const Event &src);
		~Event(void);
		Event &operator=(const Event &src);

		int			getFd(void);
		short		getState(void);
		std::string&	getResponse(void);
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


		//New
		StateType			getReqState(void);
		void				setReqState(StateType reqState);
		void				updateReqRaw1(std::string req);
		const std::string&  getReqRaw1(void);

		void setHeaderRaw(std::string header);
		void setBodyRaw(std::string body);
		std::string getHeaderRaw1(void);
		std::string getBodyRaw(void);
		void setReqRaw1(std::string req);


		void setResState(int resState);
		int getResState(void);

		void setResVect(void);

		void printVectDebug(void);

		std::string& getNextRes(void);

		void updateRes1(std::string res);

		void updateIdx(void);

		bool lastIdx(void);

		ssize_t getNumWrited(void);
		void updateNumWrited(ssize_t numWrited);

		std::string getReqPath(void);


		// for andleRes
		std::string	getFileName(void);
		void		setFileName(std::string fileName);

		size_t		getBytesReadBody(void);
		void		setBytesReadBody(size_t bytesReadBody);
		void		updateBytesReadBody(size_t bytesReadBody);

		size_t		getBodySize1(void);
		void		setBodySize1(size_t bodySize);

		const std::string&	getRes(void);
		void				setRes(std::string res);
		void				updateRes(std::string res);

		size_t				getResSize(void);
		void				setResSize(size_t resSize);

		size_t				getTotalBytesSend(void);
		void				setTotalBytesSend(size_t totalBytesSend);
		void				updateTotalBytesSend(size_t totalBytesSend);

		StateResType		getResState1(void);
		void				setResState1(StateResType resState);

		int					getErrorCode(void);
		void				setErrorCode(int errorCode);

};