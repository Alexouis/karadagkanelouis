/*
 * File             Attack_Strongest.cpp
 * Directory        ai
 * Created Date     Sunday, January 16th 2022, 2:33:09 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2022  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Attack_Strongest.h"

namespace ai{

    Attack_Strongest::Attack_Strongest (DeepAI* g_ai) : Strategy(g_ai){}

    int Attack_Strongest::work (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng){
        state::Position src = st->playerPosition(st->getActualPlayerIndex());
        
        //char t_index = st->
    }
    int Attack_Strongest::test (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng){

    }
}