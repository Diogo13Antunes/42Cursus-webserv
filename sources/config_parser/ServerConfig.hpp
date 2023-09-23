#pragma once

#include "Location.hpp"

#define MAX_BODY_SIZE	10000
#define ERROR_INVALID_VALUE						"Invalid value"
#define ERROR_INVALID_IDENTATION_LEVEL			"Invalid identation level"
#define ERROR_INVALID_LISTEN					"Invalid listen"
#define ERROR_INVALID_SERVER_NAME				"Invalid server name"
#define ERROR_INVALID_MASTER_ROOT				"Invalid master root"
#define ERROR_INVALID_CLIENT_BODY_SIZE			"Invalid client max body size"
#define ERROR_INVALID_ERROR_PAGE_KEY			"Invalid error page key"
#define ERROR_INVALID_CONFIGURATION				"Invalid configuration"
#define ERROR_MISSING_MASTER_ROOT				"Missing master root configuration"
#define ERROR_INVALID_LOCATION_ALREADY_EXIST	"Location already exit: "
#define ERROR_INVALID_MIME_TYPES				"Invalid mime types"
#define ERROR_INVALID_ERROR_PAGES				"Invalid error pages"

class ServerConfig
{
	private:

		bool		_configError;
		std::string	_configErrorMsg;

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
		void		_setListen(std::map<size_t, std::string>::iterator &it);
		void		_setServerName(std::map<size_t, std::string>::iterator &it);
		void		_setMasterRoot(std::map<size_t, std::string>::iterator &it);
		void		_setClientMaxBodySize(std::map<size_t, std::string>::iterator &it);
		std::string	_getKey(std::string &src);
		std::string	_getValue(std::string &src);
		void		_setErrorPages(std::map<size_t, std::string>::iterator &it,
			std::map<size_t, std::string>::iterator itEnd);
		void		_setLocations(std::map<size_t, std::string>::iterator &it,
			std::map<size_t, std::string>::iterator itEnd);
		void		_setMimeTypes(std::map<size_t, std::string>::iterator &it,
			std::map<size_t, std::string>::iterator itEnd);
		std::string	_getHostFromListen(std::string listen);
		std::string	_getPortFromListen(std::string listen);
		void		_addNewErrorPage(std::map<size_t, std::string>::iterator &it);
		void		_addNewMimeType(std::map<size_t, std::string>::iterator &it);
		void		_checkAllLocationsStatus(void);
		Location*	_getSpecificLocations(std::string location);
		void		_checkMasterRoot(void);

		void	_setErrorMessage(size_t line, std::string msg, std::string lineContent);
		void	_setErrorMessage(size_t line, std::string msg, std::string msg2, std::string lineContent);
		void	_setErrorMessage(std::string msg);
		void	_setErrorMessage(std::string msg, std::string msg2);

	public:
		ServerConfig(void);
		~ServerConfig(void);
		ServerConfig(std::map<size_t, std::string> configs);

		bool								getConfigError(void);
		std::string							getConfigErrorMessage(void);
		std::string							getListen(void);
		std::string							getServerName(void);
		std::string							getMasterRoot(void);
		std::map<int, std::string>			getErrorPages(void);
		std::string							getErrorPagePath(int code);
		std::map<std::string, Location>&	getLocations(void);
		size_t								getClientMaxBodySize(void);
		std::string							getFilePathByRoute(std::string route);
		std::string							getGlobalRoutePath(void);
		bool								hasRedirection(std::string route);
		void								getRedirectionInfo(std::string route, int &code, std::string &resource);
		bool								isLocationAcceptedMethod(std::string route, std::string method);
		std::string							getLocationCgi(std::string route);
		std::string							getMimeTypeByFileName(std::string src);
		std::string							getMimeTypeByFileType(std::string fileType);
		std::string 						getHost(void);
		std::string 						getPort(void);
		std::string 						getIp(void);
		void								setIp(std::string ip);
		void								setPort(std::string port);
		std::string							getUploadStore(std::string route);
		std::string							getLocationRootPath(std::string route);
		std::string							getLocationIndex(std::string route);
		std::string							getLocationAlias(std::string route);
		bool								getLocationAutoIndex(std::string route);
		bool								isConfiguredRoute(std::string path);
		size_t								getLocationBodySize(std::string route);

};
