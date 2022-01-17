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

#define move_action 0x90
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

    int Strategy::simulate_attack (std::shared_ptr<state::State> st, std::shared_ptr<engine::Engine> ng, char p_index, char t_index, int t_pos[2]){
        state::Stats p_stats1 = st->getPlayerStats(p_index);
        state::Stats t_stats1 = st->getPlayerStats(t_index);
        state::Stats p_stats2 = p_stats1;
        state::Stats t_stats2 = t_stats1;

        while(t_stats1.getAp()){
            st->simu_attack(p_index, t_index, 0, p_stats1, t_stats1);
        }
        while(t_stats2.getAp()){
            st->simu_attack(p_index, t_index, 1, p_stats2, t_stats2);
        }

        if(t_stats1.getHp() > 0 && t_stats2.getHp() >0){
            this->judicious_attack = (t_stats1.getHp() > t_stats2.getHp());
        }
        else if(t_stats1.getHp() * t_stats2.getHp() < 0){
            this->judicious_attack = (t_stats1.getHp() > 0);
        }
        else{
            this->judicious_attack = (t_stats1.getHp() < t_stats2.getHp());
        }

        while(st->get_AP(p_index) && !st->isDead(t_index)){
            ng->registerTarget(this->judicious_attack);
            ng->registerTarget(t_pos[0], t_pos[1], (char)move_action);
            this->cmdCount += 2;
        }
    }

    int Strategy::simulateEnemyTurn (std::shared_ptr<engine::Engine> nd, std::shared_ptr<state::State> st){
        
    }
}