/*
 * File             Move.cpp
 * Directory        engine
 * Created Date     Monday, December 13th 2021, 3:38:28 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Move.h"

namespace engine{
    Move::Move (float targetX, float targetY) : 
        dstX(targetX),
        dstY(targetY){

    }

    void Move::action (std::shared_ptr<state::State>& gstate) {
        gstate->moveCurrentPlayer((int)this->dstX, (int)this->dstY);
    }

    Move::~Move (){
    }

};