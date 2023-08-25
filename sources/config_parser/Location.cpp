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

Location::Location(std::string masterRoot, std::vector<std::string> locationInfo):
	_locationError(true),
	_redirection(std::make_pair(0, ""))
{
	std::vector<std::string>::iterator	it;
	std::string	key;

	_initAcceptedDefault();
	for (it = locationInfo.begin(); it != locationInfo.end(); it++)
	{
		key = getKey(*it);
		if (getNumberOfIdentations(*it) == 3)
		{
			if (!key.compare("root"))
				_setRoot(*it);
			else if (!key.compare("index"))
				_setIndex(*it);
			else if (!key.compare("cgi"))
				_setCgi(*it);
			else if (!key.compare("limit_except"))
				_setAccepted(*it);
			else if (!key.compare("upload_store"))
				_setUploadStore(*it);
			else if (!key.compare("redirect"))
				_setRedirection(it, locationInfo.end());
			else if (!key.compare("alias"))
				_setAlias(*it);
			else if (!key.compare("autoindex"))
				_setAutoIndex(*it);
			else
				_updateLocationError(false);
			if (getLocationError() == false)
				break;
		}
	}
	if (getLocationError() != false)
	{
		if (!masterRoot.empty() && _root.empty())
			_setRootMasterRoot(masterRoot);
		if (_root.empty() && masterRoot.empty())
			_updateLocationError(false);
	}
}

Location::~Location(void)
{
	//Default Location Destructor
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

std::string	Location::getAutoIndex(void)
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

void	Location::_setRoot(std::string &root)
{
	_root = getValue(root);
}

void	Location::_setRootMasterRoot(std::string &masterRoot)
{
	_root = masterRoot;
}

void	Location::_setIndex(std::string &index)
{
	_index = getValue(index);
}

void	Location::_setCgi(std::string &cgi)
{
	_cgi = getValue(cgi);
}

void	Location::_setUploadStore(std::string &uploadStore)
{
	_uploadStore = getValue(uploadStore);
}

void	Location::_setAccepted(std::string &accepted)
{
	std::string	array;
	size_t start, end;

	start = 0;
	end = 0;
	array = getValueArray(accepted);
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

void	Location::_setRedirection(std::vector<std::string>::iterator &it,
	std::vector<std::string>::iterator	itEnd)
{
	it++;
	if (it != itEnd && !isRedirection(*it))
		_updateLocationError(false);
	else
	{
		while (it != itEnd && isRedirection(*it))
		{
			if (_redirection.first && !_redirection.second.empty())
			{
				_updateLocationError(false);
				return ;
			}

			int			code;
			std::string key;
			std::string value;

			key = getKey(*it);
			value = getValue(*it);
			if (isStringEmptyOrSpaces(value)
				|| key.find_first_not_of("0123456789") != key.npos)
				_updateLocationError(false);
			else
			{
				code = strToInt(key);
				if (!isValidRedirectionCode(code))
					_updateLocationError(false);
				else
					_redirection = std::make_pair(code, value);
			}
			it++;
		}
		it--;
	}
}

void	Location::_setAlias(std::string &alias)
{
	_alias = getValue(alias);
}

void	Location::_setAutoIndex(std::string &autoindex)
{
	std::string value;

	value = getValue(autoindex);
	if (!value.compare("on"))
		_autoIndex = "on";
	else
		_autoIndex = "off";
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