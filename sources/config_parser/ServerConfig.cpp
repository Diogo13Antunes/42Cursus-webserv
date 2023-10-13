#include "ServerConfig.hpp"
#include "configs.hpp"

static size_t							getNumberOfIdentations(std::string &line);
static void								stringTrim(std::string &str);
static void								removeQuotes(std::string &str);
static bool								isInsideErrorPages(std::string &src);
static bool								isInsideLocations(std::string &src);
static bool								isNewLocations(std::string &src);
static bool								isInsideNewLocations(std::string &src);
static bool								isInsideMimeTypes(std::string &src);
static int								strToInt(std::string &str);
static bool								alreadyExistLocation(std::map<std::string, Location> &locations, std::string newLocation);
static std::pair<size_t, std::string>	createPair(size_t lineNbr, std::string lineContent);

ServerConfig::ServerConfig(void) {}

ServerConfig::ServerConfig(std::map<size_t, std::string> configs):
	_configError(true),
	_clientMaxBodySize(MAX_BODY_SIZE)
{
	std::map<size_t, std::string>::iterator	it;
	std::string								key;
	std::string								value;

	_locations.clear();

	it = configs.begin();
	while (it != configs.end() && _configError)
	{
		if (it != configs.end() && getNumberOfIdentations(it->second) == 1)
		{
			key = _getKey(it->second);
			if (key.compare("listen") == 0)
				_setListen(it);
			else if (key.compare("server_name") == 0)
				_setServerName(it);
			else if (key.compare("master_root") == 0)
				_setMasterRoot(it);
			else if (key.compare("client_max_body_size") == 0)
				_setClientMaxBodySize(it);
			else if (key.compare("error_pages") == 0)
				_setErrorPages(it, configs.end());
			else if (key.compare("location") == 0)
				_setLocations(it, configs.end());				
			else if (key.compare("mime_types") == 0)
				_setMimeTypes(it, configs.end());
			else
			{
				_setErrorMessage(it->first, ERROR_INVALID_CONFIGURATION, it->second);
				_updateConfigError(false);
			}
		}
		if (!_isValidConfigError())
			break;
		it++;
	}
	_checkMasterRoot();
	if (_isValidConfigError())
		_checkAllLocationsStatus();
}

ServerConfig::~ServerConfig(void) {}

bool	ServerConfig::getConfigError(void)
{
	return (_configError);
}

std::string	ServerConfig::getConfigErrorMessage(void)
{
	return (_configErrorMsg);
}

std::string	ServerConfig::getListen(void)
{
	return (_listen);
}

std::string	ServerConfig::getServerName(void)
{
	return (_serverName);
}

std::string ServerConfig::getMasterRoot(void)
{
	return(_masterRoot);
}

std::map<int, std::string>	ServerConfig::getErrorPages(void)
{
	return (_errorPages);
}

std::string ServerConfig::getErrorPagePath(int code)
{
	std::map<int, std::string>::iterator	it;

	it = _errorPages.find(code);
	if (it != _errorPages.end())
		return (it->second);
	return (std::string());
}

std::map<std::string, Location>&	ServerConfig::getLocations(void)
{
	return (_locations);
}

size_t	ServerConfig::getClientMaxBodySize(void)
{
	return (_clientMaxBodySize);
}

std::string	ServerConfig::getFilePathByRoute(std::string route)
{
	Location	*location;
	std::string	filePath;

	location = _getSpecificLocations(route);
	if (location)
	{
		filePath = location->getRoot();
		filePath += "/";
		filePath += location->getIndex();
	}
	return (filePath);
}

std::string	ServerConfig::getGlobalRoutePath(void)
{
	Location	*location;
	std::string	globalRoutePath;

	if (!_masterRoot.empty())
		return (_masterRoot);
	location = _getSpecificLocations("/");
	if (location)
		globalRoutePath = location->getRoot();
	return (globalRoutePath);
}

bool ServerConfig::hasRedirection(std::string route)
{
	Location	*location;

	location = _getSpecificLocations(route);
	if (location)
		return (location->hasRedirection());
	return (false);
}

void ServerConfig::getRedirectionInfo(std::string route, int &code, std::string &resource)
{
	Location								*location;
	std::pair<int, std::string>				redir;

	location = _getSpecificLocations(route);
	if (!location)
		return ;
	redir = location->getRedirection();
	code = redir.first;
	resource.assign(redir.second);
}

bool ServerConfig::isLocationAcceptedMethod(std::string route, std::string method)
{
	Location								*location;
	std::pair<int, std::string>				redir;

	location = _getSpecificLocations(route);
	if (location)
		return (location->isAcceptedMethod(method));
	return (false);
}

std::string ServerConfig::getLocationCgi(std::string route)
{
	Location	*location;

	location = _getSpecificLocations(route);
	if (!location)
		return (std::string());
	return (location->getCgi());
}

std::string	ServerConfig::getMimeTypeByFileName(std::string src)
{
	std::map<std::string, std::string>::iterator	it;
	std::string	res;
	std::string	srcWithoutDot;
	size_t	i;

	i = src.find_first_of(".");
	if (i != src.npos)
		srcWithoutDot = src.substr(i + 1);
	
	it = _mimeTypes.find(src);
	if (it != _mimeTypes.end())
		res = it->second;
	else
	{
		it = _mimeTypes.find(srcWithoutDot);
		if (it != _mimeTypes.end())
			res = it->second;
	}
	return (res);
}

std::string	ServerConfig::getMimeTypeByFileType(std::string fileType)
{
	std::map<std::string, std::string>::iterator	it;

	it = _mimeTypes.find(fileType);
	if (it != _mimeTypes.end())
		return (it->second);
	return (std::string());
}


std::string ServerConfig::getHost(void)
{
	return (_host);
}

std::string ServerConfig::getPort(void)
{
	return (_port);
}

std::string ServerConfig::getIp(void)
{
	return (_ip);
}

void ServerConfig::setIp(std::string ip)
{
	_ip = ip;
}

void ServerConfig::setPort(std::string port)
{
	_port = port;
}

std::string ServerConfig::getUploadStore(std::string route)
{
	Location	*location;

	location = _getSpecificLocations(route);
	if (!location)
		return (std::string());
	return (location->getUploadStore());
}



std::string ServerConfig::getLocationRootPath(std::string route)
{
	Location *location;

	location = _getSpecificLocations(route);
	if (location)
		return (location->getRoot());
	return (std::string());
}

std::string ServerConfig::getLocationIndex(std::string route)
{
	Location *location;

	location = _getSpecificLocations(route);
	if (location)
		return (location->getIndex());
	return (std::string());
}

std::string ServerConfig::getLocationAlias(std::string route)
{
	Location *location;

	location = _getSpecificLocations(route);
	if (location)
		return (location->getAlias());
	return (std::string());
}

bool	ServerConfig::getLocationAutoIndex(std::string route)
{
	Location *location;

	location = _getSpecificLocations(route);
	if (!location)
		return (false);
	return (location->getAutoIndex());
}

bool ServerConfig::isConfiguredRoute(std::string path)
{
	if (_getSpecificLocations(path))
		return (true);
	return (false);
}

size_t ServerConfig::getLocationBodySize(std::string route)
{
	Location	*location;
	size_t		maxBodySize;

	location = _getSpecificLocations(route);
	if (location)
	{
		maxBodySize = location->getClientMaxBodySize();
		if (maxBodySize)
			return (maxBodySize);
	}
	return (_clientMaxBodySize);
}

/* PRIVATE METHODS */

void	ServerConfig::_updateConfigError(bool newConfigError)
{
	_configError = newConfigError;
}

bool	ServerConfig::_isValidConfigError(void)
{
	return (_configError);
}

std::string	ServerConfig::_getValue(std::string &src)
{
	std::string value;
	size_t		index;

	index = src.find_first_of(":");
	value = src.substr(index + 1);
	stringTrim(value);
	removeQuotes(value);
	return (value);
}

std::string	ServerConfig::_getKey(std::string &src)
{
	std::string	key;
	size_t		begin;
	size_t		end;

	begin = src.find_first_not_of(EMPTY_SPACE);
	end = src.find_first_of(":");
	key = src.substr(begin, end - begin);
	stringTrim(key);
	removeQuotes(key);
	return (key);
}

void	ServerConfig::_setListen(std::map<size_t, std::string>::iterator &it)
{
	_listen = _getValue(it->second);
	if (_listen.empty())
	{
		_setErrorMessage(it->first, ERROR_INVALID_LISTEN, it->second);
		_updateConfigError(false);
	}
	else 
	{
		_host = _getHostFromListen(_listen);
		_port = _getPortFromListen(_listen);
	}
}

void	ServerConfig::_setServerName(std::map<size_t, std::string>::iterator &it)
{
	_serverName = _getValue(it->second);
	if (_serverName.empty())
	{
		_setErrorMessage(it->first, ERROR_INVALID_SERVER_NAME, it->second);
		_updateConfigError(false);
	}
}

void	ServerConfig::_setMasterRoot(std::map<size_t, std::string>::iterator &it)
{
	_masterRoot = _getValue(it->second);
	if (_masterRoot.empty())
	{
		_setErrorMessage(it->first, ERROR_INVALID_MASTER_ROOT, it->second);
		_updateConfigError(false);
	}
}

void	ServerConfig::_setErrorPages(std::map<size_t, std::string>::iterator &it,
	std::map<size_t, std::string>::iterator itEnd)
{
	std::string temp;

	temp = _getValue(it->second);
	if (!temp.empty())
	{
		_updateConfigError(false);
		_setErrorMessage(it->first, ERROR_INVALID_VALUE,it->second);
		return ;
	}
	it++;
	if (!isInsideErrorPages(it->second))
	{
		it--;
		_setErrorMessage(it->first, ERROR_INVALID_ERROR_PAGES,it->second);
		_updateConfigError(false);
		it++;
	}
	else
	{
		while (it != itEnd && isInsideErrorPages(it->second))
		{
			_addNewErrorPage(it);
			it++;
		}
		it--;
	}
}

void	ServerConfig::_addNewErrorPage(std::map<size_t, std::string>::iterator &it)
{
	std::string key;
	int			intKey;
	std::string value;

	key = _getKey(it->second);
	value = _getValue(it->second);
	if (key.find_first_not_of("0123456789") == key.npos)
	{
		intKey = strToInt(key);
		_errorPages.insert(std::make_pair(intKey, value));
	}
	else
	{
		_setErrorMessage(it->first, ERROR_INVALID_ERROR_PAGE_KEY, it->second);
		_updateConfigError(false);
	}
}

void	ServerConfig::_setClientMaxBodySize(std::map<size_t, std::string>::iterator &it)
{
	std::stringstream	out;
	std::string strValue;
	size_t	size;

	strValue = _getValue(it->second);
	if (strValue.find_first_not_of("0123456789") != strValue.npos)
	{
		_updateConfigError(false);
		_setErrorMessage(it->first, ERROR_INVALID_CLIENT_BODY_SIZE,it->second);
	}
	else
	{
		out << strValue;
		out >> size;
		_clientMaxBodySize = size;
	}
}

void	ServerConfig::_setLocations(std::map<size_t, std::string>::iterator &it,
	std::map<size_t, std::string>::iterator itEnd)
{
	std::string						newLocationURL;
	std::map<size_t, std::string>	locationInfo;
	std::string temp;

	temp = _getValue(it->second);
	if (!temp.empty())
	{
		_updateConfigError(false);
		_setErrorMessage(it->first, ERROR_INVALID_VALUE,it->second);
		return ;
	}
	it++;
	if (!isInsideLocations(it->second))
	{
		_setErrorMessage(it->first, ERROR_INVALID_IDENTATION_LEVEL,it->second);
		_updateConfigError(false);
	}
	else
	{
		while (it != itEnd && isInsideLocations(it->second))
		{
			if (it != itEnd && isNewLocations(it->second))
			{
				newLocationURL = _getKey(it->second);	
				if (alreadyExistLocation(_locations, newLocationURL))
				{
					_updateConfigError(false);
					_setErrorMessage(it->first, ERROR_INVALID_LOCATION_ALREADY_EXIST, newLocationURL,it->second);
					break;
				}
				it++;
				while (it != itEnd && isInsideNewLocations(it->second))
				{
					locationInfo.insert(createPair(it->first, it->second));
					it++;
				}
				_locations.insert(std::make_pair(newLocationURL, Location(_masterRoot, _clientMaxBodySize, locationInfo)));
				locationInfo.clear();
				it--;
			}
			else
			{
				_setErrorMessage(it->first, ERROR_INVALID_IDENTATION_LEVEL, it->second);
				_updateConfigError(false);
				break;
			}
			it++;
		}
		it--;
	}
}

void	ServerConfig::_setMimeTypes(std::map<size_t, std::string>::iterator &it,
	std::map<size_t, std::string>::iterator itEnd)
{
	std::string temp;

	temp = _getValue(it->second);
	if (!temp.empty())
	{
		_updateConfigError(false);
		_setErrorMessage(it->first, ERROR_INVALID_VALUE,it->second);
		return ;
	}
	it++;
	if (!isInsideMimeTypes(it->second))
	{
		it--;
		_updateConfigError(false);
		_setErrorMessage(it->first, ERROR_INVALID_MIME_TYPES,it->second);
		it++;
	}
	else
	{
		while (it != itEnd && isInsideMimeTypes(it->second))
		{
			_addNewMimeType(it);
			it++;
		}
		it--;
	}
}

std::string ServerConfig::_getHostFromListen(std::string listen)
{
	std::string	host;
	size_t		idx;

	idx = listen.find(":");
	if (idx != listen.npos)
		host = listen.substr(0, idx);
	else if (listen.find_first_not_of("0123456789") != std::string::npos)
		host = listen;
	else
		host = DEFAULT_HOST;
	return (host);
}

std::string ServerConfig::_getPortFromListen(std::string listen)
{
	std::string	port;
	size_t		idx;

	idx = listen.find(":");
	if (idx != listen.npos)
		port = listen.substr(idx + 1);
	else if (listen.find_first_not_of("0123456789") != std::string::npos)
		port = DEFAULT_PORT_STR;
	else
		port = listen;
	return (port);
}

void	ServerConfig::_addNewMimeType(std::map<size_t, std::string>::iterator &it)
{
	std::string key;
	std::string value;

	key = _getKey(it->second);
	value = _getValue(it->second);
	_mimeTypes.insert(std::make_pair(key, value));
}

void	ServerConfig::_checkAllLocationsStatus(void)
{
	std::map<std::string, Location>::iterator	it;

	for (it = _locations.begin(); it != _locations.end(); it++)
	{
		if (it->second.getLocationError() == false)
		{
			_updateConfigError(false);
			_setErrorMessage(it->second.getLocationErrorMsg());
			break;
		}
	}
}

Location	*ServerConfig::_getSpecificLocations(std::string location)
{
	std::map<std::string, Location>::iterator	it;
	size_t										routeSize;

	if (_locations.empty())
		return (NULL);
	it = _locations.find(location);
	if (it != _locations.end())
		return (&(it->second));
	routeSize = location.size();	
	if (routeSize > 0 && location.at(routeSize - 1) == '/')
	{
		location.erase(routeSize - 1);
		it = _locations.find(location);
		if (it != _locations.end())
			return (&(it->second));
	}
	return (NULL);
}

void	ServerConfig::_checkMasterRoot(void)
{
	if (_masterRoot.empty())
	{
		_setErrorMessage(ERROR_MISSING_MASTER_ROOT);
		_updateConfigError(false);
	}
}

void	ServerConfig::_setErrorMessage(size_t line, std::string msg, std::string lineContent)
{
	std::stringstream ss;

	ss << line;
	_configErrorMsg = msg + " | Line: " + std::string(ss.str()) + "\n";
	_configErrorMsg += lineContent;
}

void	ServerConfig::_setErrorMessage(size_t line, std::string msg, std::string msg2, std::string lineContent)
{
	std::stringstream ss;

	ss << line;
	_configErrorMsg = msg + msg2 + " | Line: " + std::string(ss.str()) + "\n";
	_configErrorMsg += lineContent;
}

void	ServerConfig::_setErrorMessage(std::string msg)
{
	_configErrorMsg = msg;
}

void	ServerConfig::_setErrorMessage(std::string msg, std::string msg2)
{
	_configErrorMsg = msg + msg2;
}

/* STATIC FUNCTIONS */

static bool	isInsideErrorPages(std::string &src)
{
	if (getNumberOfIdentations(src) == 2)
		return (true);
	return (false);
}

static bool	isInsideLocations(std::string &src)
{
	if (getNumberOfIdentations(src) >= 2)
		return (true);
	return (false);
}

static bool	isNewLocations(std::string &src)
{
	if (getNumberOfIdentations(src) == 2)
		return (true);
	return (false);
}

static bool	isInsideNewLocations(std::string &src)
{
	if (getNumberOfIdentations(src) > 2)
		return (true);
	return (false);
}

static bool	isInsideMimeTypes(std::string &src)
{
	if (getNumberOfIdentations(src) == 2)
		return (true);
	return (false);
}

static size_t	getNumberOfIdentations(std::string &line)
{
	size_t	index;
	size_t	identations = 0;
	size_t	nbrSpaces = 0;

	if (line.empty())
		return (0);
	index = line.find_first_not_of(" ");
	for (size_t i = 0; i <= index; i++)
	{
		if (nbrSpaces == 2)
		{
			identations++;
			nbrSpaces = 0;
		}
		if (line[i] == ' ')
			nbrSpaces++;
	}
	return (identations);
}

static void	stringTrim(std::string &str)
{
	std::string	trimmed = str;
	size_t		start = trimmed.find_first_not_of(EMPTY_SPACE);
	size_t		end = trimmed.find_last_not_of(EMPTY_SPACE);

	if (start != std::string::npos)
		trimmed = trimmed.substr(start);
	if (end != std::string::npos)
		trimmed = trimmed.substr(0, end + 1);
	str = trimmed;
}

static void	removeQuotes(std::string &str)
{
	size_t	begin, end;

	begin = str.find_first_of("\"");
	if (begin != str.npos)
	{
		end = str.find_last_of("\"");
		if (end != str.npos)
			str = str.substr(begin + 1, end - 1);
	}
}

static int	strToInt(std::string &str)
{
	std::stringstream	out(str);
	int					intValue;
	out >> intValue;
	return (intValue);
}

static bool	alreadyExistLocation(std::map<std::string, Location> &locations, std::string newLocation)
{
	std::map<std::string, Location>::iterator	it;

	it = locations.find(newLocation);
	if (it != locations.end())
		return (true);
	return (false);
}

static std::pair<size_t, std::string>	createPair(size_t lineNbr, std::string lineContent)
{
	return (std::make_pair<size_t, std::string>(static_cast<size_t>(lineNbr), static_cast<std::string>(lineContent)));
}
