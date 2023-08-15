/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:57:28 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/15 16:54:13 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Signals
{
	private:
		static bool _stopSignal;

	public:
		static void init(void);
		static void	handler(int signal);
		static bool	isStopSignalTriggered(void);
};
