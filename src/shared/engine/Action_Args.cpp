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
    Action_Args::Action_Args (std::shared_ptr<state::State>& gstate, int x, int y, state::Position old_pos, int old_mp):
    state(gstate)
    {
        point[0] = x;
        point[1] = y;
        this->old_pos_mp[0] = old_pos.x;
        this->old_pos_mp[1] = old_pos.y;
        this->old_pos_mp[3] = old_mp;
    }

    Action_Args::Action_Args (std::shared_ptr<state::State>& gstate, int x, int y, int old_ap_thp[2]):
    state(gstate)
    {
        point[0] = x;
        point[1] = y;
        this->old_ap_thp[0] = old_ap_thp[0];
        this->old_ap_thp[1] = old_ap_thp[1];
    }
    Action_Args::Action_Args (std::shared_ptr<state::State>& gstate, char selected, char old_attack_index):
    state(gstate),
    selected(selected),
    old_attack_index(old_attack_index)
    {}
    Action_Args::Action_Args (engine::Engine* ngine, char selected):
    ngine(ngine),
    selected(selected)
    {}

    Action_Args::~Action_Args (){

    }
}