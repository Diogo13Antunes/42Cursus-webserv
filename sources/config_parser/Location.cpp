#include "Location.hpp"

static bool			isRedirection(std::string src);
static std::string	getKey(std::string &src);
static std::string	getValue(std::string &src);
static std::string	getValueArray(std::string &src);
static void			stringTrim(std::string &str);
static void			removeQuotes(std::string &str);
static void			removeBraquets(std::string &array);
static size_t		getNumberOfIdentations(std::string &line);
static int			strToInt(std::string &str);
static bool			isValidRedirectionCode(int code);
static bool			isStringEmptyOrSpaces(std::string &str);

Location::Location(void):
	_locationError(true)
{
	//Default Location Constructor
}

Location::Location(std::string masterRoot, std::map<size_t, std::string> locationInfo):
	_locationError(true),
	_redirection(std::make_pair(0, "")),
	_autoIndex(false)
{
	std::map<size_t, std::string>::iterator	it;
	std::string	key;

	_initAcceptedDefault();
	for (it = locationInfo.begin(); it != locationInfo.end(); it++)
	{
		key = getKey(it->second);
		if (getNumberOfIdentations(it->second) == 3)
		{
			if (!key.compare("root"))
				_setRoot(it);
			else if (!key.compare("index"))
				_setIndex(it);
			else if (!key.compare("cgi"))
				_setCgi(it);
			else if (!key.compare("allowed"))
				_setAccepted(it);
			else if (!key.compare("upload_store"))
				_setUploadStore(it);
			else if (!key.compare("redirect"))
				_setRedirection(it, locationInfo.end());
			else if (!key.compare("alias"))
				_setAlias(it);
			else if (!key.compare("autoindex"))
				_setAutoIndex(it);
			else if (!key.compare("client_max_body_size"))
				_setClientMaxBodySize(it);
			else
			{
				_updateLocationError(false);
				_setErrorMessage(it->first, ERROR_INVALID_LOCATION_OPTION, it->second);
			}
			if (getLocationError() == false)
				break;
		}
	}
	if (getLocationError() != false)
	{
		if (_root.empty() && masterRoot.empty())
		{
			_updateLocationError(false);
			_setErrorMessage(it->first, ERROR_INVALID_LOCATION_WITHOUT_ROOT_MROOT, it->second);
		}
	}
	if (!_root.empty() && !_alias.empty())
	{
		_updateLocationError(false);
		_setErrorMessage(it->first, ERROR_INVALID_LOCATION_WITHOUT_ROOT_ALIAS, it->second);
	}
}

Location::~Location(void)
{
	//Default Location Destructor
}

std::string	Location::getLocationErrorMsg(void)
{
	return (_locationErrorMsg);
}

bool	Location::getLocationError(void)
{
	return (_locationError);
}

std::string	Location::getRoot(void)
{
	return (_root);
}

std::string	Location::getIndex(void)
{
	return (_index);
}

std::string	Location::getCgi(void)
{
	return (_cgi);
}

std::string	Location::getUploadStore(void)
{
	return (_uploadStore);
}

std::string	Location::getAlias(void)
{
	return (_alias);
}

std::vector<std::string>	Location::getAccepted(void)
{
	if (_accepted.size() > 0)
		return (_accepted);
	return (_acceptedDefault);
}

std::pair<int, std::string>	Location::getRedirection(void)
{
	return (_redirection);
}

bool	Location::getAutoIndex(void)
{
	return (_autoIndex);
}

bool	Location::existCgi(void)
{
	if (!_cgi.empty())
		return (true);
	return (false);
}

bool	Location::existUploadStore(void)
{
	if (!_uploadStore.empty())
		return (true);
	return (false);
}

bool	Location::hasRedirection(void)
{
	if (_redirection.first && !_redirection.second.empty())
		return (true);
	return (false);
}

bool	Location::isAcceptedMethod(std::string method)
{
	std::vector<std::string>::iterator	it;

	if (_accepted.size() > 0)
	{
		for (it = _accepted.begin(); it != _accepted.end(); it++)
		{
			if (it->compare(method) == 0)
				return (true);
		}
	}
	else
	{
		if (method.compare("GET") == 0)
			return (true);
	}
	return (false);
}

size_t Location::getClientMaxBodySize(void)
{
	return (_clientMaxBodySize);
}

/* PRIVATE METHODS */

void	Location::_initAcceptedDefault(void)
{
	_acceptedDefault.reserve(1);
	_acceptedDefault.push_back("GET");
}

void	Location::_updateLocationError(bool newLocationError)
{
	_locationError = newLocationError;
}

void	Location::_setRoot(std::map<size_t, std::string>::iterator &it)
{
	_root = getValue(it->second);
	if (_root.empty())
	{
		_updateLocationError(false);
		_setErrorMessage(it->first, ERROR_INVALID_LOCATION_ROOT, it->second);
	}
}

void	Location::_setRootMasterRoot(std::string &masterRoot)
{
	_root = masterRoot;
}

void	Location::_setIndex(std::map<size_t, std::string>::iterator &it)
{
	_index = getValue(it->second);
	if (_index.empty())
	{
		_updateLocationError(false);
		_setErrorMessage(it->first, ERROR_INVALID_LOCATION_INDEX, it->second);
	}
}

void	Location::_setCgi(std::map<size_t, std::string>::iterator &it)
{
	_cgi = getValue(it->second);
	if (_cgi.empty())
	{
		_updateLocationError(false);
		_setErrorMessage(it->first, ERROR_INVALID_LOCATION_CGI, it->second);
	}
}

void	Location::_setUploadStore(std::map<size_t, std::string>::iterator &it)
{
	_uploadStore = getValue(it->second);
	if (_uploadStore.empty())
	{
		_updateLocationError(false);
		_setErrorMessage(it->first, ERROR_INVALID_LOCATION_UPLOAD_STORE, it->second);
	}
}

void	Location::_setAccepted(std::map<size_t, std::string>::iterator &it)
{
	std::string	array;
	size_t start, end;

	start = 0;
	end = 0;
	array = getValueArray(it->second);
	while ((end = array.find(",", start)) != std::string::npos)
	{
		_accepted.push_back(array.substr(start, end - start));
		start = end + 1;
	}
	_accepted.push_back(array.substr(start));
	for (size_t i = 0; i < _accepted.size(); i++)
	{
		stringTrim(_accepted.at(i));
		removeQuotes(_accepted.at(i));
	}
}

void	Location::_setRedirection(std::map<size_t, std::string>::iterator &it,
	std::map<size_t, std::string>::iterator	itEnd)
{
	if (it++ != itEnd)
		it++;
	if (it != itEnd && !isRedirection(it->second))
	{
		_updateLocationError(false);
		_setErrorMessage(it->first, ERROR_INVALID_LOCATION_REDIRECTION, it->second);
	}
	else
	{
		while (it != itEnd && isRedirection(it->second))
		{
			if (_redirection.first && !_redirection.second.empty())
			{
				_updateLocationError(false);
				_setErrorMessage(it->first, ERROR_INVALID_LOCATION_REDIRECTION, it->second);
				return ;
			}

			int			code;
			std::string key;
			std::string value;

			key = getKey(it->second);
			value = getValue(it->second);
			if (isStringEmptyOrSpaces(value)
				|| key.find_first_not_of("0123456789") != key.npos)
			{
				_updateLocationError(false);
				_setErrorMessage(it->first, ERROR_INVALID_LOCATION_REDIRECTION, it->second);
			}
			else
			{
				code = strToInt(key);
				if (!isValidRedirectionCode(code))
				{
					_setErrorMessage(it->first, ERROR_INVALID_LOCATION_REDIRECTION_CODE, it->second);
					_updateLocationError(false);
				}
				else
					_redirection = std::make_pair(code, value);
			}
			it++;
		}
		it--;
	}
}

void	Location::_setAlias(std::map<size_t, std::string>::iterator &it)
{
	_alias = getValue(it->second);
	if (_alias.empty())
	{
		_updateLocationError(false);
		_setErrorMessage(it->first, ERROR_INVALID_LOCATION_ALIAS, it->second);
	}
}

void	Location::_setAutoIndex(std::map<size_t, std::string>::iterator &it)
{
	std::string value;

	value = getValue(it->second);
	if (value.empty())
	{
		_updateLocationError(false);
		_setErrorMessage(it->first, ERROR_INVALID_LOCATION_AUTOINDEX, it->second);
	}
	if (!value.compare("on"))
		_autoIndex = true;
}

void	Location::_setClientMaxBodySize(std::map<size_t, std::string>::iterator &it)
{
	std::stringstream	out;
	std::string strValue;
	size_t	size;

	strValue = getValue(it->second);
	if (strValue.find_first_not_of("0123456789") != strValue.npos)
	{
		_updateLocationError(false);
		_setErrorMessage(it->first, ERROR_INVALID_LOCATION_CLIENT_BODY_SIZE, it->second);
	}
	else
	{
		out << strValue;
		out >> size;
		_clientMaxBodySize = size;
	}
}

void	Location::_setErrorMessage(size_t line, std::string msg, std::string lineContent)
{
	std::stringstream ss;

	ss << line;
	_locationErrorMsg = msg + " | Line: " + std::string(ss.str()) + "\n";
	_locationErrorMsg += lineContent;
}

void	Location::_setErrorMessage(size_t line, std::string msg, std::string msg2, std::string lineContent)
{
	std::stringstream ss;

	ss << line;
	_locationErrorMsg = msg + msg2 + " | Line: " + std::string(ss.str()) + "\n";
	_locationErrorMsg += lineContent;
}

void	Location::_setErrorMessage(std::string msg)
{
	_locationErrorMsg = msg;
}

void	Location::_setErrorMessage(std::string msg, std::string msg2)
{
	_locationErrorMsg = msg + msg2;
}

/* STATIC FUNCTIONS */

static bool	isRedirection(std::string src)
{
	if (getNumberOfIdentations(src) == 4)
		return (true);
	return (false);
}

static std::string	getValue(std::string &src)
{
	std::string value;
	size_t		index;

	index = src.find_first_of(":");
	value = src.substr(index + 1);
	stringTrim(value);
	removeQuotes(value);
	return (value);
}

static std::string	getValueArray(std::string &src)
{
	std::string value;
	size_t		index;

	index = src.find_first_of(":");
	value = src.substr(index + 1);
	stringTrim(value);
	removeBraquets(value);
	return (value);
}

static std::string	getKey(std::string &src)
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

static void	removeBraquets(std::string &array)
{
	size_t	begin, end;

	begin = array.find_first_of("[");
	if (begin != array.npos)
	{
		end = array.find_last_of("]");
		if (end != array.npos)
			array = array.substr(begin + 1, end - 1);
	}
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

static int	strToInt(std::string &str)
{
	std::stringstream	out(str);
	int					intValue;
	out >> intValue;
	return (intValue);
}

static bool	isValidRedirectionCode(int code)
{
	switch (code)
	{
		case 301:
			return (true);
		case 302:
			return (true);
		case 303:
			return (true);
		case 307:
			return (true);
		case 308:
			return (true);
	}
	return (false);
}

static bool	isStringEmptyOrSpaces(std::string &str)
{
	if (!str.empty())
	{
		if (str.find_first_not_of(EMPTY_SPACE) != str.npos)
			return (false);
	}
	return (true);
}