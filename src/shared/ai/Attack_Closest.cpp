/*
 * File             Attack_Closest.cpp
 * Directory        ai
 * Created Date     Sunday, January 16th 2022, 5:49:58 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2022  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Attack_Closest.h"
#include <iostream>

namespace ai {

    Attack_Closest::Attack_Closest (DeepAI* g_ai, std::shared_ptr<state::State>& gstate, std::shared_ptr<engine::Engine>& ngine) : 
    Strategy(g_ai, gstate, ngine) {}

    int Attack_Closest::test (int buf_index){
        std::cout << "exploit5546465\n";
        t_pos[buf_index].push(new int[2]);
        p_index[buf_index].push(gstate->getActualPlayerIndex());
        std::cout << "exploit\n";
        t_index[buf_index].push(gstate->closestEnemyIndexTo(p_index[buf_index].back(), t_pos[buf_index].back()));
        std::cout << "exploit\n";
        std::cout << "p_index = " << (int)p_index[buf_index].back() << std::endl;
        std::cout << "t_index = " << (int)t_index[buf_index].back() << std::endl;
        std::cout << "t pos = " << t_pos[buf_index].back()[0] <<" " << t_pos[buf_index].back()[1] << std::endl;
        int score = start_simulation(buf_index);
        return score;
    }
}