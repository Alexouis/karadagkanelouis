/*
 * File             Robot.cpp
 * Directory        ai
 * Created Date     Sunday, January 23rd 2022, 2:38:44 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2022  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Robot.h"
#include "HeuristicAI.h"
#include "DeepAI.h"

namespace ai {
    Robot::Robot (engine::Engine* ngine){
        ngine->bind(this);
        this->ais[state::from::random   ] = std::unique_ptr<AI>         (new AI          (ngine));
        this->ais[state::from::heuristic] = std::unique_ptr<HeuristicAI>(new HeuristicAI (ngine));
        this->ais[state::from::deep_ai  ] = std::unique_ptr<DeepAI>     (new DeepAI      (ngine));
    }

    void Robot::bind(std::shared_ptr<state::State>& gstate){
        this->gstate = gstate;
    }

    void Robot::exploit (){
        this->ais[this->gstate->get_Input()]->exploit();
    }

    Robot::~Robot (){  }
}