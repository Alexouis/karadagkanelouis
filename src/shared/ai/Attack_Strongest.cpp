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

#define weak_attack 0x0
#define strg_attack 0x1
#define move_action 0x90
#include <iostream>

namespace ai{

    Attack_Strongest::Attack_Strongest (DeepAI* g_ai, std::shared_ptr<state::State>& gstate, std::shared_ptr<engine::Engine>& ngine) : 
    Strategy(g_ai, gstate, ngine){}

    int Attack_Strongest::test (int buf_index){
        std::cout << "Attack_Strongest" << std::endl;
        t_pos[buf_index].push(new int[2]);
        p_index[buf_index].push(gstate->getActualPlayerIndex());
        t_index[buf_index].push(gstate->strngestEnemyIndexTo(p_index[buf_index].back(), t_pos[buf_index].back()));
        int score = 0;
        std::cout << "p_index = " << (int)p_index[buf_index].back() << std::endl;
        std::cout << "t_index = " << (int)t_index[buf_index].back() << std::endl;
        std::cout << "t pos = " << t_pos[buf_index].back()[0] <<" " << t_pos[buf_index].back()[1] << std::endl;
        if(t_index[buf_index].back()==-1)
        {
            t_pos[buf_index].pop();
            p_index[buf_index].pop();
            t_index[buf_index].pop();
            return 0;
        }
        score += start_simulation(buf_index);
        return score;
    }
}