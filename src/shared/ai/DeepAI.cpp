/*
 * File             AdvancedAI.cpp
 * Directory        ai
 * Created Date     Tuesday, January 4th 2022, 4:30:30 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2022  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "DeepAI.h"
#include "Attack_Strongest.h"
#include "Attack_Closest.h"
#include "Attack_Weakest.h"
#include "Attack_Most_InDanger.h"

#define ANALYSIS true
#define CMDCOUNT1 0
#define CMDCOUNT2 1
#define BUF_INDEX_1 0
#define BUF_INDEX_2 1
#define PASS 0x20  //[targetCode code value] =  [0 010 0000]
#define SIMU_PASS 0x21  //[targetCode code value] =  [0 010 0000]


namespace ai{
    DeepAI::DeepAI(){
        this->strategies[0] = std::unique_ptr<Attack_Strongest    >(new Attack_Strongest    (this));
        this->strategies[1] = std::unique_ptr<Attack_Closest      >(new Attack_Closest      (this));
        this->strategies[2] = std::unique_ptr<Attack_Weakest      >(new Attack_Weakest      (this));
        this->strategies[3] = std::unique_ptr<Attack_Most_InDanger>(new Attack_Most_InDanger(this));
    }

    void DeepAI::exploit(){
        this->exploit(0);
    }

    /*  Permet de simuler l’action que l’IA a choisi d’effectuer comme le fait de cliquer sur un bouton 
        ou sur la map par exemple  */
    void DeepAI::exploit(bool work_is_simu){
        if(this->mode == ANALYSIS){
            this->gstate->turn_all_in_AI();
            char this_p_index = this->gstate->getActualPlayerIndex();
            int score, maxScore = 0;
            int i=0, max_hp = this->gstate->get_HP(this_p_index);
            for(auto &strategy : this->strategies){
                score = strategy->test(this->gstate, this->ngine, 0);
                this->simu_othersTurn_for(this_p_index, BUF_INDEX_2);

                score -= (max_hp - this->gstate->get_HP(this_p_index));

                if(score > maxScore){
                    maxScore = score;
                    this->bestStrategy_index = i;
                }
                i++;
                this->backup(BUF_INDEX_1);
            }
        }

        this->strategies[this->bestStrategy_index]->apply(this->gstate, this->ngine, BUF_INDEX_1);
        
    }

    /*  Annule les commandes exécutés selon le type de simulation effectuée (recherche de stratégie ou 
        simulation d’action après avoir trouvé la meilleur stratégie)   */
    void DeepAI::backup(int buf_infex){
        while(this->cmdCount[buf_infex]){
            this->ngine->undo();
            this->cmdCount[buf_infex]--;
        }
    }

    //  Permet d’incrémenter la valeur de cmdCount lorsqu’un commande est exécutée.
    inline void DeepAI::incCmdCount(int count, int buf_infex){
        this->cmdCount[buf_infex] += count;
    }

    /*  Permet de permet de simuler le tour des autres joueurs en prenant comme référence le joueur dont
        l’index est passé en argument   */
    void DeepAI::simu_othersTurn_for (char actu_p_index, int buf_infex){
        char curr;
        do{
            this->ngine->registerTarget((char)SIMU_PASS);
            this->incCmdCount(1,BUF_INDEX_1);
            curr = this->gstate->getActualPlayerIndex();
            this->simu_bestStrategyFor_curr();
            this->strategies[this->bestStrategy_index]->apply(this->gstate, this->ngine, BUF_INDEX_2);
        }while ((curr != actu_p_index) && this->gstate->get_HP(actu_p_index));
    }

    //  Permet de tester les différentes stratégies et déterminer la meilleure pour l’IA actuelle.
    int DeepAI::simu_bestStrategyFor_curr (){
        int score, maxScore = 0;
        int i=0;
        for(auto &strategy : this->strategies){
            score = strategy->test(this->gstate, this->ngine, BUF_INDEX_2);
            if(score > maxScore){
                maxScore = score;
                this->bestStrategy_index = i;
            }
            i++;
            this->backup(BUF_INDEX_2);
        }
    }


    DeepAI::~DeepAI(){}

    
}