/*
 * File             Action_Args.cpp
 * Directory        engine
 * Created Date     Friday, December 31st 2021, 6:33:28 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Action_Args.h"

namespace engine{
    Action_Args::Action_Args (std::shared_ptr<state::State>& gstate, int x, int y):
    state(gstate)
    {
        point[0] = x;
        point[1] = y;
    }
    Action_Args::Action_Args (std::shared_ptr<state::State>& gstate, char selected):
    state(gstate),
    selected(selected)
    {}
    Action_Args::Action_Args (engine::Engine* ngine, char selected):
    ngine(ngine),
    selected(selected)
    {}

    Action_Args::~Action_Args (){

    }
}