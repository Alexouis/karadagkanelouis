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

    void Action::move(std::shared_ptr<state::State>& gstate, int dstX, int dstY){
        gstate->moveCurrentPlayer(dstX, dstY);
    }

    void Action::attack(std::shared_ptr<state::State>& gstate, int targetX, int targetY){
        gstate->makeAttackOn(targetX, targetY);
    }

    void Action::select(std::shared_ptr<state::State>& gstate, int boxX, int boxY){
        gstate->setCurrPlayerAttack(boxX);
    }

    void Action::passTurn (std::shared_ptr<state::State>& gstate, int targetX, int targetY){
        gstate->passTurn();
    }

    void Action::doNothing (std::shared_ptr<state::State>& gstate, int targetX, int targetY){
        return;
    }


}