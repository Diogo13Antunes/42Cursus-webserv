#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

#define EMPTY_SPACE			"\n\t\r "

#define ERROR_INVALID_LOCATION_ROOT					"Invalid location root"
#define ERROR_INVALID_LOCATION_INDEX				"Invalid location index"
#define ERROR_INVALID_LOCATION_CGI					"Invalid location cgi"
#define ERROR_INVALID_LOCATION_UPLOAD_STORE			"Invalid location upload store"
#define ERROR_INVALID_LOCATION_IDENTATION_LEVEL		"Invalid location identation level"
#define ERROR_INVALID_LOCATION_REDIRECTION			"Invalid location redirection"
#define ERROR_INVALID_LOCATION_REDIRECTION_CODE		"Invalid location redirection code"
#define ERROR_INVALID_LOCATION_ALIAS				"Invalid location alias"
#define ERROR_INVALID_LOCATION_AUTOINDEX			"Invalid location autoindex"
#define ERROR_INVALID_LOCATION_CLIENT_BODY_SIZE		"Invalid location client max body size"
#define ERROR_INVALID_LOCATION_OPTION				"Invalid location option"
#define ERROR_INVALID_LOCATION_WITHOUT_ROOT_MROOT	"Invalid location without both root and master root"
#define ERROR_INVALID_LOCATION_WITHOUT_ROOT_ALIAS	"Invalid location without root and alias"

class Location
{
	bool							_locationError;
	std::string						_locationErrorMsg;
	std::string						_root;
	std::string						_index;
	std::string						_cgi;
	std::string						_uploadStore;
	std::vector<std::string>		_accepted;
	std::vector<std::string>		_acceptedDefault;
	std::pair<int, std::string>		_redirection;
	std::string						_alias;
	bool							_autoIndex;
	size_t							_clientMaxBodySize;

	void	_initAcceptedDefault(void);
	void	_updateLocationError(bool newLocationError);
	void	_setRoot(std::map<size_t, std::string>::iterator &it);
	void	_setRootMasterRoot(std::string &masterRoot);
	void	_setIndex(std::map<size_t, std::string>::iterator &it);
	void	_setCgi(std::map<size_t, std::string>::iterator &it);
	void	_setUploadStore(std::map<size_t, std::string>::iterator &it);
	void	_setAccepted(std::map<size_t, std::string>::iterator &it);
	void	_setRedirection(std::map<size_t, std::string>::iterator &it,
		std::map<size_t, std::string>::iterator	itEnd);
	void	_setAlias(std::map<size_t, std::string>::iterator &it);
	void	_setAutoIndex(std::map<size_t, std::string>::iterator &it);
	void	_setClientMaxBodySize(std::map<size_t, std::string>::iterator &it);

	void	_setErrorMessage(size_t line, std::string msg, std::string lineContent);
	void	_setErrorMessage(size_t line, std::string msg, std::string msg2, std::string lineContent);
	void	_setErrorMessage(std::string msg);
	void	_setErrorMessage(std::string msg, std::string msg2);

	public:
		Location(void);
		Location(std::string masterRoot, std::map<size_t, std::string> locationInfo);
		~Location(void);

		std::string					getLocationErrorMsg(void);

		bool						getLocationError(void);
		std::string					getRoot(void);
		std::string					getIndex(void);
		std::string					getCgi(void);
		std::string					getUploadStore(void);
		std::string					getAlias(void);
		std::vector<std::string>	getAccepted(void);
		std::pair<int, std::string>	getRedirection(void);
		bool						hasRedirection(void);
		bool						existCgi(void);
		bool						existUploadStore(void);
		bool						isAcceptedMethod(std::string method);
		bool						getAutoIndex(void);
		size_t						getClientMaxBodySize(void);
};
