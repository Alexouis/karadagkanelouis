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
#include "Attack_Closest.h"
#include "Attack_Weakest.h"
#include "Attack_Most_InDanger.h"

#define ANALYSIS true

namespace ai{
    DeepAI::DeepAI(){
        this->strategy[0] = std::unique_ptr<Attack_Strongest    >(new Attack_Strongest    (this));
        this->strategy[1] = std::unique_ptr<Attack_Closest      >(new Attack_Closest      (this));
        this->strategy[2] = std::unique_ptr<Attack_Weakest      >(new Attack_Weakest      (this));
        this->strategy[3] = std::unique_ptr<Attack_Most_InDanger>(new Attack_Most_InDanger(this));
    }

    void DeepAI::exploit(){
        if(this->mode == ANALYSIS){
            
        }
    }
    DeepAI::~DeepAI(){}

    
}