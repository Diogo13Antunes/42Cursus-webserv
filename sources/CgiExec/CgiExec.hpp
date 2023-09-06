/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiExec.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:56:39 by dsilveri          #+#    #+#             */
/*   Updated: 2023/09/06 14:31:15 by dsilveri         ###   ########.fr       */
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
		static void			_freeEnvVariables(char **env);
		static int			_execute(char **env, std::string scriptPath, int *p1, int *p2);

	public:
		static int		execute(Event *event);
		static bool		isEnded(Event *event);
		
};
