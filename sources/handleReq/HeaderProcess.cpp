/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderProcess.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:30:18 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/23 14:04:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "HeaderProcess.hpp"

StateType HeaderProcess::handle(void)
{
    std::cout << "HeaderProcess" << std::endl;
    return (HEADER_PROCESS);
}
