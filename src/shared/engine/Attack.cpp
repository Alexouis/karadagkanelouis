/*
 * File             Attack.cpp
 * Directory        engine
 * Created Date     Monday, December 13th 2021, 3:58:22 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Attack.h"

namespace engine{

    Attack::Attack (float targetX, float targetY) : 
        targetX(targetX),
        targetY(targetY){

    }

    void Attack::action (std::shared_ptr<state::State>& gstate){
        gstate->makeAttackOn((int)this->targetX, (int)this->targetY);
    }

    Attack::~Attack (){
    }
}