#include "RequestData.hpp"

RequestData::RequestData(void)
{
	//Default RequestData Constructor
}

RequestData::~RequestData(void)
{
	//Default RequestData Destructor
}

void	RequestData::setRequestLine(std::string &src)
{
	size_t		index_1;
	size_t		index_2;
	std::string	element[3];

	index_1 = src.find_first_of(" ");
	index_2 = src.find_last_of(" ");
	if (index_1 == index_2 || index_1 == src.npos || index_2 == src.npos)
		throw InvalidRequestLineException();
	element[0] = RequestDataUtils::getRequestLineElement(src, 0, index_1);
	element[1] = RequestDataUtils::getRequestLineElement(src, index_1, index_2);
	element[2] = RequestDataUtils::getRequestLineElement(src, index_2, src.size());

	for (size_t i = 0; i < 3; i++)
	{
		if (!element[i].empty())
			_requestLine.push_back(element[i]);
		else
		{
			_requestLine.clear();
			throw InvalidRequestLineException();
		}
	}
	// if (!RequestDataUtils::isValidRequestLine(_requestLine))
		// throw InvalidRequestLineException();
}

void	RequestData::setRequestHeader(std::map<std::string, std::vector<std::string> > &src)
{
	_requestHeader = src;
}

void	RequestData::setRequestBody(std::string &src)
{
	_requestBody = src;
}

std::vector<std::string>	RequestData::getRequestLine(void)
{
	return (_requestLine);
}

std::map<std::string, std::vector<std::string> >	RequestData::getRequestHeader(void)
{
	return (_requestHeader);
}

std::string	RequestData::getRequestBody(void)
{
	return (_requestBody);
}

std::string RequestData::getPath(void)
{
	return (_requestLine.at(1));
}

/* Exceptions */

const char *RequestData::InvalidRequestLineException::what(void) const throw()
{
	return ("InvalidRequestLineException: The request line is invalid or badly formatted.");
}
