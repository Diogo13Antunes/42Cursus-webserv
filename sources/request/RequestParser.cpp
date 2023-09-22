#include "RequestParser.hpp"
#include "StringUtils.hpp"

#define DIGITS					"0123456789"
#define MAX_REQUEST_TARGET_LEN	8000
#define	MAX_HEADER_SIZE			24576
#define NAX_HEADER_LINE_SIZE	8192

typedef enum
{
	SUCCESSFULL_HEADER = 0,
	BAD_REQUEST = 400,
	URI_TOO_LONG = 414,
	INTERNAL_SERVER_ERROR = 500,
	NOT_IMPLEMENTED = 501
} RequestStatusCode;

static std::vector<std::string> getElementValue(const std::string &src);
static bool						isValidNumberOfQuotes(const std::string &src);
static std::string				getReadyValue(const std::string &src, size_t index1, size_t index2);
static std::string				getRequestLineElement(const std::string &src, size_t i1, size_t i2);
static std::string				getPath(std::string &src);
static std::string				getQueryStr(std::string &src);
static bool						isValidServerName(std::string &serverName);
static bool						withConsecutiveChars(std::string &src, char c);

RequestParser::RequestParser(void) : _statusCode(SUCCESSFULL_HEADER) {}

RequestParser::~RequestParser(void) {}

int RequestParser::headerParse(std::string &header)
{
	std::istringstream iss(header);
	std::string line;
	bool isFirstLine = true;

	try
	{
		if (header.size() > MAX_HEADER_SIZE)
			return (BAD_REQUEST);
		while (std::getline(iss, line))
		{
			line += "\n";
			if (line.find_first_not_of("\r\n") == line.npos)
				break;
			if (line.size() > MAX_REQUEST_TARGET_LEN)
				_statusCode = URI_TOO_LONG;
			else if (isFirstLine)
			{
				_requestLine = StringUtils::stringTrim(line);
				_statusCode = _requestLineParser();
				isFirstLine = false;
			}
			else
				_statusCode = _addHeaderElement(line);
			if (_statusCode)
				return (_statusCode);
		}
		_statusCode = _isValidRequestHeader();
	}
	catch(const std::exception& e)
	{
		_statusCode = INTERNAL_SERVER_ERROR;
	}
	return (_statusCode);
}

void RequestParser::bodyParse(std::string &body)
{
	_requestBody = body;
}

void RequestParser::updateReqBody(std::string &body)
{
	_requestBody += body;
}

int RequestParser::_isValidRequestHeader(void)
{
	if (!_statusCode)
	{
		_statusCode = _isValidHeader();
		if (!_statusCode)
			_statusCode = _isValidHost();
		if (!_statusCode)
			_statusCode = _isValidContentLenght();
		if (!_statusCode)
			_statusCode = _hasContentLengthAndTransferEncoded();
		if (!_statusCode)
			_statusCode = _isValidTransferEncodingValue();
	}
	return (_statusCode);
}

int RequestParser::_isValidContentLenght(void)
{
	std::map<std::string, std::vector<std::string> >::iterator it;
	std::string contentLen;

	it = _requestHeader.find("content-length");
	if (it != _requestHeader.end())
	{
		if ((*it).second.size() == 1)
			contentLen = (*it).second.at(0).c_str();
		else
			return (BAD_REQUEST);
	}
	if (!contentLen.empty())
	{
		if (contentLen.find_first_not_of(DIGITS) != contentLen.npos)
			return (BAD_REQUEST);
	}
	return (SUCCESSFULL_HEADER);
}

std::string RequestParser::getRequestLine(void)
{
	return (_requestLine);
}

std::string RequestParser::getRequestBody(void)
{
	return (_requestBody);
}

std::string& RequestParser::getRequestBodyRef(void)
{
	return (_requestBody);
}

std::map<std::string, std::vector<std::string> > RequestParser::getRequestHeader(void)
{
	return (_requestHeader);
}

std::string RequestParser::getReqLineTarget(void)
{
	return (_reqLineTarget);
}

std::string RequestParser::getReqLineHttpVersion(void)
{
	return (_reqLineHttpVersion);
}

std::string RequestParser::getReqLineMethod(void)
{
	return (_reqLineMethod);
}

std::string RequestParser::getReqLinePath(void)
{
	return (_reqLinePath);
}

std::string RequestParser::getConnectionField(void)
{
	std::vector<std::string> connection;

	connection = this->getHeaderField("connection");
	if (!connection.empty())
		return (connection.at(0));
	return (std::string());
}

std::string RequestParser::getQueryString(void)
{
	return (_queryString);
}

std::vector<std::string> RequestParser::getHeaderField(std::string fieldName)
{
	std::map<std::string, std::vector<std::string> >::iterator it;

	it = _requestHeader.find(fieldName);
	if (it != _requestHeader.end())
		return (it->second);
	return (std::vector<std::string>());
}

/* Class Private Functions */

int RequestParser::_isValidHeader(void)
{
	std::map<std::string, std::vector<std::string> >::const_iterator it;
	std::string key;
	std::vector<std::string> value;

	for (it = _requestHeader.begin(); it != _requestHeader.end(); it++)
	{
		key = (*it).first;
		value = (*it).second;
		if (StringUtils::isStringEmptyOrSpaces(key))
			return (BAD_REQUEST);
	}
	return (SUCCESSFULL_HEADER);
}

int RequestParser::_getContentLen(void)
{
	std::map<std::string, std::vector<std::string> >::iterator it;
	int len = -1;

	it = _requestHeader.find("content-length");
	if (it != _requestHeader.end())
	{
		if ((*it).second.size() == 1)
			len = std::atoi((*it).second.at(0).c_str());
	}
	return (len);
}

std::pair<std::string, std::vector<std::string> > RequestParser::_getHeaderFieldPair(std::string &src)
{
	std::string key;
	std::vector<std::string> value;
	std::string temp;
	size_t index;

	index = src.find_first_of(":");
	if (index != src.npos)
	{
		key = src.substr(0, index);
		StringUtils::stringToLower(key);
		if (src.find_first_not_of(WHITE_SPACE, index + 1) != src.npos)
		{
			temp = src.substr(src.find_first_of(":") + 1, src.size());
			temp = StringUtils::stringTrim(temp);
			value = getElementValue(temp);
		}
	}
	return (std::make_pair(key, value));
}

int RequestParser::_requestLineParser(void)
{
	size_t index_1;
	size_t index_2;

	index_1 = _requestLine.find_first_of(" ");
	index_2 = _requestLine.find_last_of(" ");
	if (index_1 == index_2 || index_1 == _requestLine.npos || index_2 == _requestLine.npos)
		return (BAD_REQUEST);
	_reqLineMethod = getRequestLineElement(_requestLine, 0, index_1);
	_reqLineTarget = getRequestLineElement(_requestLine, index_1, index_2);
	_reqLineHttpVersion = getRequestLineElement(_requestLine, index_2, _requestLine.size());
	if (_reqLineMethod.empty() || _reqLineTarget.empty() || _reqLineHttpVersion.empty())
		return (BAD_REQUEST);
	if (StringUtils::hasWhiteSpaces(_reqLineTarget))
		return (BAD_REQUEST);
	if (_reqLineTarget.size() > MAX_REQUEST_TARGET_LEN)
		return (URI_TOO_LONG);
	_requestTargetParser();
	return (SUCCESSFULL_HEADER);
}

void RequestParser::_requestTargetParser(void)
{
	if (_reqLineTarget.size() > 1)
	{
		StringUtils::removeConsecutiveChars(_reqLineTarget, '/');
		_reqLinePath = getPath(_reqLineTarget);
		_queryString = getQueryStr(_reqLineTarget);
	}
	else
		_reqLinePath = _reqLineTarget;
}

int RequestParser::_addHeaderElement(std::string &line)
{
	std::pair<std::string, std::vector<std::string>  > header;

	header = _getHeaderFieldPair(line);
	if (StringUtils::hasWhiteSpaces(header.first) || _existAlreadyHeader(header.first))
	{
		_requestHeader.clear();
		return (BAD_REQUEST);
	}
	_requestHeader.insert(header);
	return (SUCCESSFULL_HEADER);
}

bool	RequestParser::_existAlreadyHeader(std::string &key)
{
	std::map<std::string, std::vector<std::string> >::iterator	it;

	it = _requestHeader.find(key);
	if (it != _requestHeader.end())
		return (true);
	return (false);
}

int RequestParser::_hasContentLengthAndTransferEncoded(void)
{
	std::map<std::string, std::vector<std::string> >::iterator it1;
	std::map<std::string, std::vector<std::string> >::iterator it2;

	it1 = _requestHeader.find("content-length");
	it2 = _requestHeader.find("transfer-encoding");
	if (it1 != _requestHeader.end() && it2 != _requestHeader.end())
		return (BAD_REQUEST);
	return (SUCCESSFULL_HEADER);
}

int	RequestParser::_isValidTransferEncodingValue(void)
{
	std::vector<std::string>	header;

	header = getHeaderField("transfer-encoding");
	if (header.empty())
		return (SUCCESSFULL_HEADER);
	if (header.size() != 1 || header.at(0).compare("chunked"))
		return (NOT_IMPLEMENTED);
	return (SUCCESSFULL_HEADER);
}

int	RequestParser::_isValidHost(void)
{
	std::vector<std::string>	header;
	std::string					serverName;

	header = getHeaderField("host");
	if (header.empty() || header.size() != 1)
		return (BAD_REQUEST);
	serverName = header.at(0);
	if (!isValidServerName(serverName))
		return (BAD_REQUEST);
	return (SUCCESSFULL_HEADER);
}

/* Static Functions */

static std::vector<std::string> getElementValue(const std::string &src)
{
	std::vector<std::string> elements;
	std::string temp;
	size_t nbrQuotes = 0;
	size_t j = 0;

	if (isValidNumberOfQuotes(src))
	{
		for (size_t i = 0; i < src.size(); i++)
		{
			if (src[i] == '\"')
				nbrQuotes++;
			if (i == src.size() - 1 || (src[i] == ',' && nbrQuotes % 2 == 0))
			{
				temp = getReadyValue(src, i, j);
				elements.push_back(temp);
				j = i + 1;
			}
		}
	}
	return (elements);
}

static bool isValidNumberOfQuotes(const std::string &src)
{
	size_t nbrQuotes = 0;

	for (size_t i = 0; i < src.size(); i++)
	{
		if (src[i] == '\"')
			nbrQuotes++;
	}
	if (nbrQuotes % 2 != 0)
		return (false);
	return (true);
}

static std::string getReadyValue(const std::string &src, size_t index1, size_t index2)
{
	const std::string notValueChars = "\n\r\t\", ";
	std::string result;
	size_t i1 = 0;
	size_t i2 = 0;

	i1 = src.find_first_not_of(notValueChars, index2);
	i2 = src.find_last_not_of(notValueChars, index1);
	result = src.substr(i1, i2 - i1 + 1);
	return (result);
}

static std::string getRequestLineElement(const std::string &src, size_t i1, size_t i2)
{
	std::string result;
	size_t len;

	len = i2 - i1 + 1;
	if (len > 0 && i1 < src.length())
	{
		result = src.substr(i1, len);
		result = StringUtils::stringTrim(result);
	}
	return (result);
}

static std::string getPath(std::string &src)
{
	std::string	path;
	size_t		index;

	path = src;
	index = path.find_first_of('?');
	if (index != src.npos)
		path = path.substr(0, index);
	return (path);
}

static std::string	getQueryStr(std::string &src)
{
	std::string	queryString;
	size_t		i;

	i = src.find_first_of("?");
	if (i != src.npos)
		queryString = src.substr(i + 1);
	return (queryString);
}

static bool	isValidServerName(std::string &serverName)
{
	if (serverName.empty())
		return (false);
	serverName = StringUtils::stringTrim(serverName);
	if (serverName.find_first_of("/") != serverName.npos)
		return (false);
	if (withConsecutiveChars(serverName, '.'))
		return (false);
	if (serverName.size() == 1 && serverName[0] == '.')
		return (false);
	return (true);
}

static bool	withConsecutiveChars(std::string &src, char c)
{
	bool found = false;

	for (size_t i = 0; i < src.size(); i++)
	{
		if (src[i] == c && found)
			return (true);
		if (src[i] == c)
			found = true;
		else
			found = false;
	}
	return (false);
}
