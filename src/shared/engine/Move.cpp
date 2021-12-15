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

    void Move::action (void) {
        this->currentState->setCurrentPlayerPosition(this->targetX, this->targetY);
    }

};