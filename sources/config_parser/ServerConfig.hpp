#pragma once

#include "Location.hpp"

class ServerConfig
{
	private:

		bool		_configError;

		std::string	_serverName;
		std::string	_listen;
		std::string	_masterRoot;
		std::string _host;
		std::string _ip;
		std::string _port;
		size_t		_clientMaxBodySize;

		std::map<std::string, Location>			_locations;
		std::map<int, std::string>				_errorPages;
		std::map<std::string, std::string>		_mimeTypes;

		void		_updateConfigError(bool newConfigError);
		bool		_isValidConfigError(void);
		void		_setListen(std::string newListen);
		void		_setServerName(std::string newServerName);
		void		_setMasterRoot(std::string newMasterRoot);
		void		_setClientMaxBodySize(std::string &value);
		std::string	_getKey(std::string &src);
		std::string	_getValue(std::string &src);
		void		_setErrorPages(std::vector<std::string>::iterator &it,
			std::vector<std::string>::iterator itEnd);
		void		_setLocations(std::vector<std::string>::iterator &it,
			std::vector<std::string>::iterator itEnd);
		void		_setMimeTypes(std::vector<std::string>::iterator &it,
			std::vector<std::string>::iterator itEnd);
		std::string	_getHostFromListen(std::string listen);
		std::string	_getPortFromListen(std::string listen);
		void		_addNewErrorPage(std::string &src);
		void		_addNewMimeType(std::string &src);
		void		_checkAllLocationsStatus(void);
		Location*	_getSpecificLocations(std::string location);
		void		_checkMasterRoot(void);

	public:

		//ServerConfig(const ServerConfig &src);
		//ServerConfig &operator=(const ServerConfig &src);

		ServerConfig(void);
		~ServerConfig(void);
		ServerConfig(std::vector<std::string> configs);

		bool								getConfigError(void);
		std::string							getListen(void);
		std::string							getServerName(void);
		std::string							getMasterRoot(void);
		std::map<int, std::string>			getErrorPages(void);
		std::map<std::string, Location>&	getLocations(void);
		size_t								getClientMaxBodySize(void);
		std::string							getFilePathByRoute(std::string route);
		std::string							getGlobalRoutePath(void);
		bool								hasRedirection(std::string route);
		void								getRedirectionInfo(std::string route, int &code, std::string &resource);
		std::string							getCgiScriptName(std::string route);
		std::string							existMimeType(std::string src);
		std::string 						getHost(void);
		std::string 						getPort(void);
		std::string 						getIp(void);
		void								setIp(std::string ip);
		void								setPort(std::string port);
		std::string							getUploadStore(std::string route);
		std::string							getLocationRootPath(std::string route);
		std::string							getMasterRootPath(std::string route);
		std::string							getLocationIndex(std::string route);
		std::string							getLocationAlias(std::string route);
		bool								isLocationAutoIndex(std::string route);

};
