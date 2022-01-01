/*
 * File             Action.cpp
 * Directory        engine
 * Created Date     Tuesday, December 21st 2021, 3:18:20 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Action.h"
#include <iostream>
namespace engine{
    Action::Action(){

    }

    void Action::move (std::unique_ptr<Action_Args>& args){
        args->state->moveCurrentPlayer(args->point[0], args->point[1]);
    }

    void Action::attack (std::unique_ptr<Action_Args>& args){
        args->state->makeAttackOn(args->point[0], args->point[1]);
    }

    void Action::select (std::unique_ptr<Action_Args>& args){
        args->state->setCurrPlayerAttack(args->selected);
    }

    void Action::passTurn (std::unique_ptr<Action_Args>& args){
        args->state->passTurn();
    }

    void Action::doNothing (std::unique_ptr<Action_Args>& args){
        return;
    }

    void Action::startGame (std::unique_ptr<Action_Args>& args){
        args->state->chronoStart(state::State::chronoStep, state::State::chronoCount);
    }


}