#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "RequestDataUtils.hpp"

class RequestData
{
	private:

		std::vector<std::string>	_requestLine;

	public:

		void						setRequestLine(std::string &src);
		std::vector<std::string>	getRequestLine(void);

		RequestData(void);
		~RequestData(void);

		class InvalidRequestLineException: public std::exception
		{
			public:
				const char *what() const throw();
		};

};
