#include "RequestDataUtils.hpp"

RequestDataUtils::RequestDataUtils(void)
{
	//Default RequestDataUtils Constructor
}

RequestDataUtils::~RequestDataUtils(void)
{
	//Default RequestDataUtils Destructor
}

std::string	RequestDataUtils::stringTrim(const std::string &str)
{
	std::string	trimmed;
	size_t		start;
	size_t		end;
	size_t		len;

	start = str.find_first_not_of(WHITE_SPACE);
	end = str.find_last_not_of(WHITE_SPACE);
	len = end - start + 1;
	trimmed = str.substr(start, len);
	return (trimmed);
}

std::string	RequestDataUtils::getRequestLineElement(const std::string &src, size_t i1, size_t i2)
{
	std::string	result;
	size_t		len;

	result.clear();
	len = i2 - i1 + 1;
	if (len > 0 && i1 < src.length())
	{
		result = src.substr(i1, len);
		result = stringTrim(result);
	}
	return (result);
}

std::string	RequestDataUtils::getPath(std::string &src)
{
	std::string res;
	std::size_t	index;

	index = src.find_first_of('?');
	if (index != src.npos)
		res = src.substr(0, index);
	else
		res = src;
	return (res);
}

std::string	RequestDataUtils::getQueryStringURL(std::string &src)
{
	std::string res;
	std::size_t	index;

	index = src.find_first_of('?');
	if (index != src.npos)
		res = src.substr(index + 1);
	return (res);
}

/*
Alterar caso seja preciso adicionar mais metodos
Metodos:
-> GET
-> POST
-> DELETE
*/
/* bool	RequestDataUtils::isValidRequestLine(std::vector<std::string> &requestLine)
{
	std::string	method;

	method = requestLine.at(0).c_str();
	if (method.compare("GET") != 0 && method.compare("POST") != 0 && method.compare("DELETE") != 0)
		return (false);
	return (true);
} */
