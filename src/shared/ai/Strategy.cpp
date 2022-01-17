/*
 * File             Strategy.cpp
 * Directory        ai
 * Created Date     Sunday, January 16th 2022, 4:51:30 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2022  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Strategy.h"


namespace ai {
    Strategy::Strategy (DeepAI* g_ai){
        //this->g_ai = std::shared_ptr<DeepAI>(g_ai);
    }

    Strategy::~Strategy(){}

    void Strategy::pick_GoodPosition (char p_index, std::shared_ptr<state::State> st){
        char src_index = st->getActualPlayerIndex();
        state::Position src  = st->playerPosition(src_index);
        state::Position dst  = st->playerPosition(p_index);
        int mp = st->get_MP(src_index);
        int attack_range = st->get_Attack(src_index).range;

        st->BFS_Shortest_Path(dst, src);
        if(mp+attack_range < (*st)[dst].distance){
            this->strategic_position = state::Position(-1,-1);
            return;
        }

        this->strategic_position = dst;
        while(attack_range){
            this->strategic_position = (*st)[this->strategic_position].next_grid;
            attack_range--;
        }

    }

    int Strategy::simulate_attack (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng, char selected_attack){
        
    }
    int Strategy::simulateEnemyTurn (std::shared_ptr<engine::Engine> nd, std::shared_ptr<state::State> st){

    }
}