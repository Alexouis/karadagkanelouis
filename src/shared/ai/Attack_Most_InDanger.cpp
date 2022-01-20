/*
 * File             Attack_Most_InDanger.cpp
 * Directory        ai
 * Created Date     Sunday, January 16th 2022, 5:51:29 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2022  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Attack_Most_InDanger.h"
#define SPELL1 0x0 //[targetCode code value] =  [0 000 0000]
#define SPELL2 0x1 //[targetCode code value] =  [0 000 0001]
#define SPELL3 0x2 //[targetCode code value] =  [0 000 0010]
#define SPELL4 0x3 //[targetCode code value] =  [0 000 0011]
#define SPELL5 0x4 //[targetCode code value] =  [0 000 0100]
#define MENU 0x10  //[targetCode code value] =  [0 001 0000]
#define PASS 0x20  //[targetCode code value] =  [0 010 0000]
#define MOVE 0x90  //[targetCode code value] =  [1 001 0000]

namespace ai {

    Attack_Most_InDanger::Attack_Most_InDanger (DeepAI* g_ai, std::shared_ptr<state::State>& gstate, std::shared_ptr<engine::Engine>& ngine) : 
    Strategy(g_ai, gstate, ngine) {}

    int Attack_Most_InDanger::test (int buf_index){
        t_pos[buf_index].push(new int[2]);
        p_index[buf_index].push(gstate->getActualPlayerIndex());
        t_index[buf_index].push(gstate->enemyWithLessHp_Of(p_index[buf_index].back(), t_pos[buf_index].back()));
        int score = start_simulation(buf_index);
        return score;
    }

}