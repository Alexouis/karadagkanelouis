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
#include <iostream>


namespace ai {
    Strategy::Strategy (DeepAI* g_ai, std::shared_ptr<state::State>& gstate, std::shared_ptr<engine::Engine>& ngine){
        this->g_ai = std::shared_ptr<DeepAI>(g_ai);
        this->gstate = gstate;
        this->ngine = ngine;
        this->p_index.resize(2);
        this->t_index.resize(2);
        this->t_pos.resize(2);
        this->savedPos.resize(2);

    }

    Strategy::~Strategy(){}

    int Strategy::test (int buf_index){}

    //  Applique la meilleur stratégie trouvée par la fonction test()
    int Strategy::apply (int buf_index){
        
        if(t_pos[buf_index].size() < 1){ return -1; }
        if(savedPos[buf_index].front().x != -1){
            if(iteration == 0){
                iteration++;
                if(savedPos[buf_index].front().x != -2){
                    //then move to good position
                    ngine->registerTarget(savedPos[buf_index].front().x, savedPos[buf_index].front().y, (char)move_action);
                    if(buf_index){
                        ngine->execute(); 
                        g_ai->incCmdCount(1, 0);
                    }
                }
            }
        //abort();

attack_again:      //then  attack
            if(gstate->hasEnough_AP(p_index[buf_index].front(), judicious_attack[buf_index].front()) && !gstate->isDead(t_index[buf_index].front())){
                ngine->registerTarget(judicious_attack[buf_index].front());
                ngine->registerTarget(t_pos[buf_index].front()[0], t_pos[buf_index].front()[1], (char)move_action);
                if(buf_index){
                    ngine->execute();
                    ngine->execute();
                    g_ai->incCmdCount(2, 0); 
                    goto attack_again;
                }
                return 0;
            }
            else if(gstate->isDead(t_index[buf_index].front()) && (gstate->enemiesCount(p_index[buf_index].front()) > 0)){ 
                if(gstate->hasEnough_AP(p_index[buf_index].front(), judicious_attack[buf_index].front())){
                    iteration = 0;
                    if(t_pos[buf_index].size() > 1){
                        popQueues (buf_index);
                        return apply(buf_index);
                    }
                }
                else{
                    if(t_pos[buf_index].size() > 0){ popQueues (buf_index); }
                    return -1;
                }
            }
        }

        if(t_pos[buf_index].size() > 0){ popQueues (buf_index);  }
        return -1;
    }

    /*  Permet de trouver la position optimale à laquelle le joueur devrait se placer 
        Il s’agit de la position la moins couteuse en PM, qui permettrait d’attaquer l’ennemi ciblé par 
        la stratégie    */
    void Strategy::pick_GoodPosition (int buf_index){
        state::Position src  = gstate->playerPosition(p_index[buf_index].back());
        state::Position dst  = gstate->playerPosition(t_index[buf_index].back());
        state::Position savePos[2];
        state::Stats p_stats[2];
        state::Stats t_stats[2];
        p_stats[0] = gstate->getPlayerStats(p_index[buf_index].back());
        t_stats[0] = gstate->getPlayerStats(t_index[buf_index].back());
        p_stats[1] = p_stats[0];
        t_stats[1] = t_stats[0];
        int attack_range[2];
        attack_range[0] = gstate->get_Attack(p_index[buf_index].back(), 0).range;
        attack_range[1] = gstate->get_Attack(p_index[buf_index].back(), 1).range;
        bool did_bfs = false;
        for (char i = 0; i < 2; i++){

            if(attack_range[i] >= src.grid_distance(dst)){
                savePos[i] = state::Position(-2,0);
                while(p_stats[i].getAp()){
                    gstate->simu_attack(p_index[buf_index].back(), t_index[buf_index].back(), i, p_stats[i], t_stats[i]);
                }

            }

            else{
                if(!did_bfs){
                    gstate->BFS_Shortest_Path(dst, src);
                    did_bfs = true;
                    //std::cout<< "idx0 = " << (int)p_index[buf_index].back() << "ap = "<< (int)gstate->get_AP(p_index[buf_index].back()) << std::endl;
                }
                if(p_stats[i].getMp()+attack_range[i] < (*gstate)[dst].distance){
                    savePos[i] = state::Position(-1,0);
                }
                else{
                    while(p_stats[i].getAp()){
                        gstate->simu_attack(p_index[buf_index].back(), t_index[buf_index].back(), i, p_stats[i], t_stats[i]);
                    }
                    savePos[i] = dst;
                    while(attack_range[i]){
                        savePos[i] = (*gstate)[savePos[i]].next_grid;
                        attack_range[i]--;
                    }  
                }  
            }
        }

        if((t_stats[0].getHp() > 0) && (t_stats[1].getHp() > 0)){
            judicious_attack[buf_index].push((t_stats[0].getHp() > t_stats[1].getHp()));
        }
        else if(t_stats[0].getHp() * t_stats[1].getHp() < 0){
            judicious_attack[buf_index].push((t_stats[0].getHp() > 0));
        }
        else{
            judicious_attack[buf_index].push((t_stats[0].getHp() < t_stats[1].getHp()));
        }

        savedPos[buf_index].push(savePos[judicious_attack[buf_index].back()]);
    }

    /*  Permet comme son nom l’indique de simuler une attaque en actualisant une copie des stats des personnages 
        impliquées : mise à jour des HP du joueur attaqué et des PA du joueur attaquant */
    void Strategy::simulate_attack (int buf_index){
        
        while(gstate->hasEnough_AP(p_index[buf_index].back(), judicious_attack[buf_index].back()) && !gstate->isDead(t_index[buf_index].back())){
            ngine->registerTarget(judicious_attack[buf_index].back());
            ngine->execute();
            ngine->registerTarget(t_pos[buf_index].back()[0], t_pos[buf_index].back()[1], (char)move_action);
            ngine->execute();
            g_ai->incCmdCount(2, buf_index);
        }
    }

    //  Lance la simulation de la stratégie pour déterminer son efficacité
    int Strategy::start_simulation (int buf_index){
        int score = gstate->get_HP(t_index[buf_index].back());
        int bonus = score/2;

        //gstate->
        //chooseBestAttck(buf_index);
        pick_GoodPosition(buf_index);
        
        //if good position found
        if(savedPos[buf_index].back().x != -1){
            //then move to good position
            if(savedPos[buf_index].back().x != -2){
                ngine->registerTarget(savedPos[buf_index].back().x, savedPos[buf_index].back().y, (char)move_action);
                ngine->execute();
                g_ai->incCmdCount(1,buf_index);
            }
            //the simulate attack
            simulate_attack(buf_index);

        }
        score -= gstate->get_HP(t_index[buf_index].back());

        if(gstate->isDead(t_index[buf_index].back()) && gstate->enemiesCount(p_index[buf_index].back())){ 
            score += bonus;
            if(gstate->hasEnough_AP(p_index[buf_index].back(), judicious_attack[buf_index].back())){
                score += test(buf_index);
            }
        }
        

        return score;
    }

    //  Permet de retirer des différentes queue les informations situées à l’index passé en argument
    void Strategy::popQueues (int buf_index){
        iteration = 0;
        t_pos[buf_index].pop();
        p_index[buf_index].pop();
        t_index[buf_index].pop();
        savedPos[buf_index].pop();
        judicious_attack[buf_index].pop();
    }

    void Strategy::escape (int buf_index){
        state::Position src = gstate->playerPosition(p_index[buf_index].back());
        state::Position tgt = gstate->barycentre(t_index[buf_index].back());
        int t_attack_range  = gstate->get_Attack(t_index[buf_index].back(), 0).range;
        int t_mp = gstate->get_MP(t_index[buf_index].back());
    }
}