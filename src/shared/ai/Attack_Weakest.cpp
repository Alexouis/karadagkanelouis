/*
 * File             Attack_Weakest.cpp
 * Directory        ai
 * Created Date     Sunday, January 16th 2022, 5:48:10 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2022  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Attack_Weakest.h"

namespace ai {

    Attack_Weakest::Attack_Weakest (DeepAI* g_ai) : Strategy(g_ai) {}

    int Attack_Weakest::apply (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng, int buf_infex){
        state::Position src = st->playerPosition(st->getActualPlayerIndex());
        
        //char t_index = st->
        
    }
    int Attack_Weakest::test (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng, int buf_infex){
        
    }
}