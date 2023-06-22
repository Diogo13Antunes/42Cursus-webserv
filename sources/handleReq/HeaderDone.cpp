/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderDone.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:55:14 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/22 16:50:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "HeaderDone.hpp"

IState* HeaderDone::handle(void)
{
    std::cout << "HeaderDone" << std::endl;
    return (NULL);
}
