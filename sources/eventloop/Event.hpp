/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:15:26 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/25 12:18:26 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>
#include "RequestParser.hpp"
#include "Configs.hpp"
#include "ConfigsData.hpp"
#include "StateReqType.hpp"
#include "StateResType.hpp"
#include "EventType.hpp"
#include "SocketUtils.hpp"

class Event
{
	private:
		std::string		_reqRaw;
		std::string		_reqBody;
		RequestParser	_reqParser;
		std::string		_res;
		int				_fd;
		StateReqType	_reqState;
		size_t			_resSize;
		size_t			_totalBytesSend;
		StateResType	_resState1;
		std::string		_cgiScriptResult;
		time_t			_creationTime;
		EventType		_actualState;
		bool			_finished;
		short			_connectionClosed;
		bool			_clientDisconnect;
		int				_cgiExitStatus;
		std::string		_reqHeader;
		int				_statusCode;
		std::string		_ip;
		std::string		_port;
		int				_redirectCode;
		std::string		_redirectResource;
		size_t			_fileSize;
		size_t			_fileNumBytesRead;
		ServerConfig*	_serverConf;
		int				_cgiWriteFd;
		int				_cgiReadFd;
		bool			_cgiWriteFdClosed;
		bool			_cgiReadFdClosed;
		int				_cgiPid;
		ssize_t			_numBytesSendCgi;
		bool			_cgiScriptEndend;
		std::string		_route;
		std::string		_requestPath;
		std::string		_resourcePath;
		bool			_isCgi;
		bool			_fdRemoved;
		bool			_cgiWriteFdRemoved;
		bool			_cgiReadFdRemoved;
		bool			_isStateChange;

	public:
		Event(int fd);
		~Event(void);
		Event &operator=(const Event &src);

		int						getFd(void);
		StateReqType			getReqState(void);
		void					setReqState(StateReqType reqState);
		void					updateReqRawData(const std::string &req);
		void					setReqRawData(const std::string &req);
		const std::string&		getRes(void);
		void					setRes(std::string& res);
		void					clearRes(void);
		void					eraseRes(size_t start, size_t end);
		void					updateRes(std::string& res);
		size_t					getResSize(void);
		void					setResSize(size_t resSize);
		size_t					getTotalBytesSend(void);
		void					updateTotalBytesSend(size_t totalBytesSend);
		StateResType			getResState1(void);
		void					setResState1(StateResType resState);
		std::string				getCgiScriptResult(void);
		void					updateCgiScriptResult(std::string& src);
		bool					isEventTimeout(void);
		bool					isConnectionClose(void);
		void					setConnectionClose(void);
		int						getCgiWriteFd(void);
		int						getCgiReadFd(void);
		std::string				getQueryString(void);
		std::string				getReqContentType(void);
		size_t					getReqContentLength(void);		
		std::string				getReqLineTarget(void);
		std::string				getReqLineHttpVersion(void);
		std::string				getReqLineMethod(void);
		std::string				getReqLinePath(void);
		const std::string&		getReqBody(void);
		std::string				getReqTransferEncoding(void);
		std::string				getReqHost(void);
		EventType				getActualState(void);
		void					setActualState(EventType actualState);
		bool					isFinished(void);
		void					setAsFinished(void);
		bool					isClientDisconnect(void);		
		void					setClientDisconnected(void);
		void					updateReqBody(const std::string& body);
		size_t					getReqBodySize(void);
		bool					isReqHeaderComplete(void);
		void					parseReqHeader(std::string &header);
		const std::string&		getReqHeader(void);
		std::string				getReqRawData(void);
		void					clearReqRawData(void);
		int						getStatusCode(void);
		void					setStatusCode(int statusCode);
		std::string				getIp(void);
		std::string				getPort(void);
		void					setRredirectCode(int redirectCode);
		int						getRredirectCode(void);
		void					setRredirectResource(std::string redirectResource);
		std::string				getRredirectResource(void);
		void					setFileSize(size_t fileSize);
		size_t					getFileSize(void);
		void					updateFileNumBytesRead(size_t fileNumBytesRead);
		size_t					getFileNumBytesRead(void);
		void					setServerConfing(ServerConfig* serverConf);
		ServerConfig*			getServerConfing(void);
		void					setCgiWriteFd(int cgiWriteFd);
		void					setCgiReadFd(int cgiReadFd);
		int						getCgiPid(void);
		void					setCgiPid(int pidCgi);
		ssize_t					getNumBytesSendCgi(void);
		void					updateNumBytesSendCgi(ssize_t numBytesSendCgi);
		void					closeCgiWriteFd(void);
		void					closeCgiReadFd(void);
		int						getCgiExitStatus(void);
		void					setCgiExitStatus(int cgiExitStatus);
		bool					isCgiScriptEndend(void);
		void					setCgiScriptEndend(bool cgiScriptEndend);
		std::string				getRoute(void);
		void					setRoute(std::string route);
		std::string				getRequestPath(void);
		void					setRequestPath(std::string requestPath);
		std::string				getResourcePath(void);
		void					setResourcePath(std::string resourcePath);
		void					setIsCgi(bool isCgi);
		bool					isCgi(void);
		bool					isCgiWriteFdRemoved(void);
		void					setCgiWriteFdRemoved(void);
		bool					isCgiReadFdRemoved(void);
		void					setCgiReadFdRemoved(void);
		bool					isCgiFdRemoved(int cgiFd);
		void					setCgiFdRemoved(int cgiFd, bool value);
		bool					isStateChange(void);
		void					setIsStateChange(bool isStateChange);
};
