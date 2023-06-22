/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleReq.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:15:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/06/22 16:50:26 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleReq.hpp"

HandleReq::HandleReq(void):
    _state(NULL)
{}

HandleReq::~HandleReq(void)
{
    if (_state)
        delete _state;
}

void HandleReq::handle(void)
{
    /*IState  *stateBuff;

    if (_state)
       stateBuff = _state->handle();
    if (stateBuff)
        this->setState(stateBuff);
    */
   if (_state)
       this->setState(_state->handle());
}

void HandleReq::setState(IState *state)
{
    if (state)
    {
       if (_state)
            delete _state;
        _state = state;
    }
}
