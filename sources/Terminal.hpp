#pragma once

#include <iostream>

class Terminal
{
	public:

		static void	printErrors(const char *error);
		static void	printMessages(const char *msg);

		Terminal(void);
		~Terminal(void);
};
