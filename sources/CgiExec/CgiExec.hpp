/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiExec.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:56:39 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/31 17:21:22 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Event.hpp"

class CgiExec
{
	private:
		static char**		_getEnvVars(Event *event);
		static void			_closePipe(int *p);
		static std::string	_getScriptInterpreter(std::string scriptPath);
		static int			_execute(char **env, std::string scriptPath);

	public:
		static int		execute(Event *event);
		
};
