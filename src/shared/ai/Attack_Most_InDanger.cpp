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

    Attack_Most_InDanger::Attack_Most_InDanger (DeepAI* g_ai) : Strategy(g_ai) {}

    int Attack_Most_InDanger::apply (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng, int buf_infex){
        state::Position src = st->playerPosition(st->getActualPlayerIndex());
        state::Stats stats = st->getPlayerStats(st->getActualPlayerIndex());
        if(!stats.getMp() && !stats.getAp()){
            ng->registerTarget(0, 0, (char)PASS);
        }
    }
    int Attack_Most_InDanger::test (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng, int buf_infex){
        int score = 0;
        state::Stats stats = st->getPlayerStats(st->getActualPlayerIndex());
        int target[2];
        state::Position aim;
        char actualPlayerIndex = st->getActualPlayerIndex();
        char targetIndex, selected;

        while(!stats.getMp() && !stats.getAp()){
            selected = (char)MOVE;
            targetIndex = st->enemyWithLessHp_Of(actualPlayerIndex,target);

            if(st->BFS_Shortest_Path(st->playerPosition(actualPlayerIndex),st->playerPosition(targetIndex)))
            {
                aim.x = (*st)[st->playerPosition(actualPlayerIndex)].next_grid.x;
                aim.y = (*st)[st->playerPosition(actualPlayerIndex)].next_grid.y;
                while(st->get_MP(actualPlayerIndex) > 0)
                {
                    ng->registerTarget(aim.x, aim.y,selected);
                    aim = (*st)[aim].next_grid;
                }
            }

            while(stats.getAp() > 0)
            {
                ng->registerTarget(aim.x, aim.y,selected);
                aim = (*st)[aim].next_grid;
            }
        }

        return score;
    }
}