/*
 * File             AdvancedAI.cpp
 * Directory        ai
 * Created Date     Tuesday, January 4th 2022, 4:30:30 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2022  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "DeepAI.h"
#include "Attack_Strongest.h"

namespace ai{
    DeepAI::DeepAI(){
        this->strategy.push_back(Attack_Strongest(this));
        this->strategy.push_back(Attack_Strongest(this));
        this->strategy.push_back(Attack_Strongest(this));
        this->strategy.push_back(Attack_Strongest(this));
    }
    DeepAI::~DeepAI(){}

    
}