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

    void Attack::action (){
        this->currentState->attack((int)this->targetX, (int)this->targetY);
    }
}