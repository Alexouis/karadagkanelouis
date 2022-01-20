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

    Attack_Weakest::Attack_Weakest (DeepAI* g_ai, std::shared_ptr<state::State>& gstate, std::shared_ptr<engine::Engine>& ngine) : 
    Strategy(g_ai, gstate, ngine) {}

    int Attack_Weakest::test (int buf_index){
        t_pos[buf_index].push(new int[2]);
        p_index[buf_index].push(gstate->getActualPlayerIndex());
        t_index[buf_index].push(gstate->weakestEnemyIndexTo(p_index[buf_index].back(), t_pos[buf_index].back()));
        int score = start_simulation(buf_index);
        return score;
    }
}