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

#define MIDDLEXY 11


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

    int Strategy::apply (int buf_index){
        
        std::cout << "app :" << gstate->get_AP(p_index[buf_index].front()) << std::endl;
        
        if(p_index[buf_index].size() < 1){ return -1; }
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
            std::cout << "enemiesCount_attackAgain_out :" << gstate->enemiesCount(p_index[buf_index].front()) << std::endl;
            std::cout << "get_AP_attackAgain_out :" << gstate->get_AP(p_index[buf_index].front()) << std::endl;
            std::cout << "hasEnough_AP_attackAgain_out :" << gstate->hasEnough_AP(p_index[buf_index].front(), judicious_attack[buf_index].front()) << std::endl;

            if(
                gstate->can_attack(
                    p_index[buf_index].front(), 
                    t_index[buf_index].front(), 
                    judicious_attack[buf_index].front()) && !gstate->isDead(t_index[buf_index].front()
                )
            ){
                ngine->registerTarget(judicious_attack[buf_index].front());
                ngine->registerTarget(t_pos[buf_index].front()[0], t_pos[buf_index].front()[1], (char)move_action);
                if(buf_index){
                    std::cout << "enemiesCount_attackAgain_in :" << gstate->enemiesCount(p_index[buf_index].front()) << std::endl;
                    std::cout << "get_AP_attackAgain_in :" << gstate->get_AP(p_index[buf_index].front()) << std::endl;
                    std::cout << "hasEnough_AP_attackAgain_in :" << gstate->hasEnough_AP(p_index[buf_index].front(), judicious_attack[buf_index].front()) << std::endl;

                    int prev_tHP = gstate->get_HP(t_index[buf_index].front());
                    ngine->execute();
                    ngine->execute();
                    g_ai->incCmdCount(2, 0);
                    goto attack_again; 
                }
                else { return 0; }
                
            }
            else if(gstate->isDead(t_index[buf_index].front()) && (gstate->enemiesCount(p_index[buf_index].front()) > 0)){ 
                    std::cout << "is dead_apply :" << gstate->isDead(t_index[buf_index].front()) << std::endl;
                    std::cout << "enemiesCount_apply :" << gstate->enemiesCount(p_index[buf_index].front()) << std::endl;
                    std::cout << "get_AP_apply :" << gstate->get_AP(p_index[buf_index].front()) << std::endl;
                    std::cout << "hasEnough_AP_apply :" << gstate->hasEnough_AP(p_index[buf_index].front(), judicious_attack[buf_index].front()) << std::endl;
                    iteration = 0;
                    popQueues (buf_index);
                    return apply(buf_index);
            }

            iteration = 0;
            while(p_index[buf_index].size()){ popQueues (buf_index); }
            return -1;
        }
        ngine->registerTarget(escapePos[buf_index].x, escapePos[buf_index].y, (char)move_action);
        std::cout << "apply scp = " << escapePos[buf_index].x << " " << escapePos[buf_index].y << std::endl;
        if(buf_index){
            ngine->execute();
            g_ai->incCmdCount(1,buf_index);
        }
        popQueues (buf_index);
        iteration = 0;
        // if(t_pos[buf_index].size() > 0){ popQueues (buf_index);  }
        return -1;
    }

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
        int did_scp = 0;
        for (char i = 0; i < 2; i++){

            if(attack_range[i] >= src.grid_distance(dst)){
                savePos[i] = state::Position(-2,0);
                while(p_stats[i].getAp()){
                    std::cout << "IN GP 1" << std::endl;
                    gstate->simu_attack(p_index[buf_index].back(), t_index[buf_index].back(), i, p_stats[i], t_stats[i]);
                }

            }

            else{
                    gstate->BFS_Shortest_Path(dst, src);
                    //std::cout<< "idx0 = " << (int)p_index[buf_index].back() << "ap = "<< (int)gstate->get_AP(p_index[buf_index].back()) << std::endl;
                int p_stats_mp = p_stats[i].getMp();
                savePos[i] = dst;
                while(((*gstate)[savePos[i]].next_grid != src) && (p_stats_mp) && (src.grid_distance(savePos[i]) > attack_range[i])){
                    savePos[i] = (*gstate)[savePos[i]].next_grid;
                    p_stats_mp--;
                }  
                // y
                if(attack_range[i] < src.grid_distance(savePos[i])){
                    //then esxape
                    std::cout << "IN GP 2 nexptos = "<< (*gstate)[savePos[i]].next_grid.x << " " << (*gstate)[savePos[i]].next_grid.y << std::endl;
                    //int t_attack_range  = gstate->get_Attack(t_index[buf_index].back(), 0).range;
                    //if (!did_scp){ escape(buf_index, t_stats[i].getMp() + t_attack_range); }
                    did_scp++;
                }
                else{
                    std::cout << "IN GP 3" << std::endl;
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
        if(did_scp == 2){ 
            savedPos[buf_index].push(state::Position(-1,0));
            std::cout << "IN GP ecp cond" << std::endl;
            return; 
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

        std::cout << "PGP t_stats0_HP: " << t_stats[0].getHp() << "et t_stats1_HP: " << t_stats[1].getHp() << std::endl;


        savedPos[buf_index].push(savePos[judicious_attack[buf_index].back()]);
    }

    void Strategy::simulate_attack (int buf_index){
        
        while(
            gstate->can_attack(
                p_index[buf_index].back(),
                t_index[buf_index].back(), 
                judicious_attack[buf_index].back()) && !gstate->isDead(t_index[buf_index].back()
            )
        ){
            std::cout << "IN SIMULATE ATTACK" << std::endl;
            std::cout << "is dead = " << gstate->isDead(t_index[buf_index].back()) << std::endl;
            ngine->registerTarget(judicious_attack[buf_index].back());
            ngine->execute();
            ngine->registerTarget(t_pos[buf_index].back()[0], t_pos[buf_index].back()[1], (char)move_action);
            ngine->execute();
            g_ai->incCmdCount(2, buf_index);
        }
    }

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

            score -= gstate->get_HP(t_index[buf_index].back());

            std::cout << "is dead :" << gstate->isDead(t_index[buf_index].back()) << std::endl;
            std::cout << "enemiesCount :" << gstate->enemiesCount(p_index[buf_index].back()) << std::endl;
            std::cout << "get_AP :" << gstate->get_AP(p_index[buf_index].back()) << std::endl;
            std::cout << "hasEnough_AP :" << gstate->hasEnough_AP(p_index[buf_index].back(), judicious_attack[buf_index].back()) << std::endl;

            if(gstate->isDead(t_index[buf_index].back()) && gstate->enemiesCount(p_index[buf_index].back())){ 
                score += bonus;
                std::cout << "is dead_in :" << gstate->isDead(t_index[buf_index].back()) << std::endl;
                std::cout << "enemiesCount_in :" << gstate->enemiesCount(p_index[buf_index].back()) << std::endl;
                std::cout << "get_AP_in :" << gstate->get_AP(p_index[buf_index].back()) << std::endl;
                std::cout << "hasEnough_AP_in :" << gstate->hasEnough_AP(p_index[buf_index].back(), judicious_attack[buf_index].back()) << std::endl;
                score += test(buf_index);
            }
        }

        this->escape(buf_index);
        ngine->registerTarget(escapePos[buf_index].x, escapePos[buf_index].y, (char)move_action);
        ngine->execute();
        g_ai->incCmdCount(1,buf_index);

        return score;

    }


    void Strategy::popQueues (int buf_index){
        t_pos[buf_index].pop();
        p_index[buf_index].pop();
        t_index[buf_index].pop();
        savedPos[buf_index].pop();
        judicious_attack[buf_index].pop();
    }

    void Strategy::escape (int buf_index){
        int mp = gstate->get_MP(p_index[buf_index].back());
        int tot_t_range = gstate->get_MP(t_index[buf_index].back());
        tot_t_range    += gstate->get_Attack(t_index[buf_index].back(), 0).range;
        if(!mp) { return; }
        state::Position src = gstate->playerPosition(p_index[buf_index].back());
        state::Position tgt = gstate->barycentre(t_index[buf_index].back());
        state::Position idealx, idealy, delta = src - tgt;
        state::Position dp =  (delta > 0) - (delta < 0);
        state::Position limx = state::Position(dp.x * tot_t_range + tgt.x, tgt.y);
        state::Position limy = state::Position(tgt.x, dp.y * tot_t_range + tgt.y);
        dp.x *= -1; 
        int dist, d1,d2, mindist = src.grid_distance(tgt) + tot_t_range;
        for( auto p = limx; p == limy; p += dp){
            dist    = src.grid_distance(p);
            if(dist < mindist){
                mindist = dist;
                escapePos[buf_index]   = p; 
            }
        }

        dp.x   *= -1;
        mindist = 0;
        idealx  = escapePos[buf_index] + state::Position(dp.x, 0);
        idealy  = escapePos[buf_index] + state::Position(0, dp.y);
        d1 = src.grid_distance(idealx);
        d2 = src.grid_distance(idealy);
        if     (d1 < d2){ 
            if     (gstate->inMap(idealx) && gstate->isFree(idealx)){ escapePos[buf_index] = idealx; }
            else if(gstate->inMap(idealy) && gstate->isFree(idealy)){ escapePos[buf_index] = idealy; }
            else { escapePos[buf_index] = idealx; }
        }
        else if(d1 > d2){ 
            if     (gstate->inMap(idealy) && gstate->isFree(idealy)){ escapePos[buf_index] = idealy; }
            else if(gstate->inMap(idealx) && gstate->isFree(idealx)){ escapePos[buf_index] = idealx; }
            else { escapePos[buf_index] = idealy; }
        }
        else{
            state::Position middle = state::Position(MIDDLEXY,MIDDLEXY);
            if(middle.grid_distance(idealx) < middle.grid_distance(idealy)){
                if     (gstate->inMap(idealx) && gstate->isFree(idealx)){ escapePos[buf_index] = idealx; }
                else if(gstate->inMap(idealy) && gstate->isFree(idealy)){ escapePos[buf_index] = idealy; }
                else { escapePos[buf_index] = idealx; }
            }
            else{
                if     (gstate->inMap(idealy) && gstate->isFree(idealy)){ escapePos[buf_index] = idealy; }
                else if(gstate->inMap(idealx) && gstate->isFree(idealx)){ escapePos[buf_index] = idealx; }
                else { escapePos[buf_index] = idealy; }
            }
        }

        if(!gstate->inMap(escapePos[buf_index])){ gstate->putInMap(escapePos[buf_index]); }
        if(!gstate->isFree(escapePos[buf_index])){ escapePos[buf_index] = gstate->searchFreeAround(escapePos[buf_index]); }
        gstate->BFS_Shortest_Path(src, escapePos[buf_index]);
        if((*gstate)[src].distance > mp){ 
            idealx = escapePos[buf_index];
            escapePos[buf_index] = src;
            while(mp && (escapePos[buf_index] != idealx)){
                escapePos[buf_index] = (*gstate)[escapePos[buf_index]].next_grid;
                mp--;
            }
        }
        else{
            mp = mp - (*gstate)[src].distance;
            state::Position corner = (escapePos[buf_index] < MIDDLEXY) - (escapePos[buf_index] > MIDDLEXY);
            delta.absolute();
            dp.absolute();
            if(delta.x > delta.y){ dp.x = 0; }
            else{ dp.y = 0; }
            dp = dp * corner * mp;
            delta = escapePos[buf_index] + dp;
            if(tgt.grid_distance(delta) < tgt.grid_distance(escapePos[buf_index])){ return; }
            if(!gstate->isFree(escapePos[buf_index])){ gstate->searchFreeAround(delta); }
            gstate->BFS_Shortest_Path(escapePos[buf_index], delta);
            while(mp && (escapePos[buf_index] != delta)){
                escapePos[buf_index] = (*gstate)[escapePos[buf_index]].next_grid;
                mp--;
            }
        }
        
    }
}