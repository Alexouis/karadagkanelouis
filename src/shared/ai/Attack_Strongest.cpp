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

    int Attack_Strongest::work (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng){
        state::Position src = st->playerPosition(st->getActualPlayerIndex());
        
        //char t_index = st->
    }
    int Attack_Strongest::test (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng){
        int t_pos[2];
        char p_index = st->getActualPlayerIndex();
        char t_index = st->strngestEnemyIndexTo(p_index, t_pos);
        this->pick_GoodPosition(t_index, st);
        
        //if good position found
        if(this->strategic_position.x != -1){
            //then move to good position
            ng->registerTarget(this->strategic_position.x, this->strategic_position.y, (char)move_action);
            this->judicious_attack = (char)weak_attack;
            while(st->get_AP(p_index) && !st->isDead(t_index)){
                ng->registerTarget((char)weak_attack);
                ng->registerTarget(t_pos[0], t_pos[1], (char)move_action);
                this->cmdCount += 2;
            }
            while(this->cmdCount){
                ng->undo();
                this->cmdCount--;
            }
            this->judicious_attack = (char)strg_attack;
            while(st->get_AP(p_index) && !st->isDead(t_index)){
                ng->registerTarget((char)strg_attack);
                ng->registerTarget(t_pos[0], t_pos[1], (char)move_action);
                this->cmdCount += 2;
            }
            while(this->cmdCount){
                ng->undo();
                this->cmdCount--;
            }

            //then simulate enmy turn
        }
    }
}