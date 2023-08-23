#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

#define EMPTY_SPACE			"\n\t\r "

class Location
{
	bool							_locationError;
	std::string						_root;
	std::string						_index;
	std::string						_cgi;
	std::string						_uploadStore;
	std::vector<std::string>		_accepted;
	std::vector<std::string>		_acceptedDefault;
	std::pair<int, std::string>		_redirection;
	std::string						_alias;
	bool							_autoIndex;

	void	_initAcceptedDefault(void);
	void	_updateLocationError(bool newLocationError);
	void	_setRoot(std::string &root);
	void	_setRootMasterRoot(std::string &masterRoot);
	void	_setIndex(std::string &index);
	void	_setCgi(std::string &cgi);
	void	_setUploadStore(std::string &uploadStore);
	void	_setAccepted(std::string &accepted);
	void	_setRedirection(std::vector<std::string>::iterator &it,
		std::vector<std::string>::iterator	itEnd);
	void	_setAlias(std::string &alias);
	void	_setAutoIndex(std::string &autoindex);

	public:
		Location(void);
		Location(std::string masterRoot, std::vector<std::string> locationInfo);
		~Location(void);
		
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
		bool						isAutoIndex(void);
};
