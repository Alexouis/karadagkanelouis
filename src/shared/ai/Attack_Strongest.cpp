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

namespace ai{

    Attack_Strongest::Attack_Strongest (DeepAI* g_ai) : Strategy(g_ai){}

    int Attack_Strongest::apply (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng, int buf_infex){
        int t_pos[2];
        char p_index = st->getActualPlayerIndex();
        char t_index = st->strngestEnemyIndexTo(t_index, t_pos);
        //char t_index = st->
        if(this->strategic_position[0].x != -1){
            //then move to good position
            ng->registerTarget(this->strategic_position[buf_infex].x, this->strategic_position[buf_infex] .y, (char)move_action);
            //the simulate attack
            while(st->get_AP(p_index) && !st->isDead(t_index)){
                ng->registerTarget(this->judicious_attack[buf_infex]);
                ng->registerTarget(t_pos[0], t_pos[1], (char)move_action);
                this->g_ai->incCmdCount(2, buf_infex);
            }
        }
    }
    int Attack_Strongest::test (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng, int buf_infex){
        int t_pos[2], score = 16000;
        char p_index = st->getActualPlayerIndex();
        char t_index = st->strngestEnemyIndexTo(t_index, t_pos);
        //st->
        this->pick_GoodPosition(p_index, t_index, st, buf_infex);
        
        //if good position found
        if(this->strategic_position[buf_infex].x != -1){
            //then move to good position
            ng->registerTarget(this->strategic_position[buf_infex].x, this->strategic_position[buf_infex] .y, (char)move_action);
            this->g_ai->incCmdCount(1,buf_infex);
            //the simulate attack
            this->simulate_attack(st, ng, p_index, t_index, t_pos, buf_infex);
            score -= st->get_HP(t_index);
            if(st->isDead(t_index)){ score *= 2;}
        }

        return score;
    }
}