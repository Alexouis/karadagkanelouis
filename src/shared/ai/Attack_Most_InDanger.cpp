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

namespace ai {

    Attack_Most_InDanger::Attack_Most_InDanger (DeepAI* g_ai) : Strategy(g_ai) {}

    int Attack_Most_InDanger::work (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng){
        state::Position src = st->playerPosition(st->getActualPlayerIndex());
        state::Stats st = this->gstate->getPlayerStats(this->gstate->getActualPlayerIndex());
        if(!st.getMp() && !st.getAp()){
            this->ngine->registerTarget(0, 0, (char)PASS);
        }
    }
    int Attack_Most_InDanger::test (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng){
        int score = 0;
        state::Stats st = this->gstate->getPlayerStats(this->gstate->getActualPlayerIndex());
        int target[2];
        state::Position aim;
        char actualPlayerIndex = st->actualPlayerIndex;
        char targetIndex, selected;

        while(!st.getMp() && !st.getAp()){
            selected = (char)MOVE;
            targetIndex = st->enemyWithLessHp_Of(actualPlayerIndex,target);

            if()
            if(BFS_Shortest_Path(st->playerPosition(actualPlayerIndex),st->playerPosition(targetIndex)))
            {
                aim.x = (*st)[st->playerPosition(actualPlayerIndex)].next_grid.x
                aim.y = (*st)[st->playerPosition(actualPlayerIndex)].next_grid.y
                while(st->get_MP(actualPlayerIndex) > 0)
                {
                    ng->registerTarget(aim.x, aim.y,selected);
                    aim = (*st)[aim].next_grid;
                }
            }

            while(st->get_AP(actualPlayerIndex) > 0)
            {
                ng->registerTarget(aim.x, aim.y,selected);
                aim = (*st)[aim].next_grid;
            }
        }

        return score;
    }
}