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

#include <iostream>

#define ANALYSIS true
#define CMDCOUNT1 0
#define CMDCOUNT2 1
#define BUF_INDEX_1 0
#define BUF_INDEX_2 1
#define PASS 0x20  //[targetCode code value] =  [0 010 0000]
#define SIMU_PASS 0x21  //[targetCode code value] =  [0 010 0000]


namespace ai{
    DeepAI::DeepAI(){
        this->cmdCount[0] =  0;
        this->cmdCount[1] =  0;
        this->strategies[0] = std::unique_ptr<Attack_Closest      >(new Attack_Closest      (this, gstate, ngine));
        this->strategies[1] = std::unique_ptr<Attack_Strongest    >(new Attack_Strongest    (this, gstate, ngine));
        this->strategies[2] = std::unique_ptr<Attack_Weakest      >(new Attack_Weakest      (this, gstate, ngine));
        this->strategies[3] = std::unique_ptr<Attack_Most_InDanger>(new Attack_Most_InDanger(this, gstate, ngine));
        this->bestStrategy_index[0] = 0;
        this->bestStrategy_index[1] = 0;

    }

    DeepAI::DeepAI(engine::Engine* Ngine) : AI(Ngine) {
        this->cmdCount[0] =  0;
        this->cmdCount[1] =  0;
        this->strategies[0] = std::unique_ptr<Attack_Strongest    >(new Attack_Strongest    (this, gstate, ngine));
        this->strategies[1] = std::unique_ptr<Attack_Closest      >(new Attack_Closest      (this, gstate, ngine));
        this->strategies[2] = std::unique_ptr<Attack_Weakest      >(new Attack_Weakest      (this, gstate, ngine));
        this->strategies[3] = std::unique_ptr<Attack_Most_InDanger>(new Attack_Most_InDanger(this, gstate, ngine));
        this->bestStrategy_index[0] = 0;
        this->bestStrategy_index[1] = 0;
    }

    void DeepAI::exploit(){
        this->exploit(0);
    }


    void DeepAI::exploit(bool work_is_simu){
        if(AI::test){
            AI::test  = false;
            int score = 16000, maxScore = 0;
            //this->gstate->turn_all_in_AI();
            char this_p_index = this->gstate->getActualPlayerIndex();
            int i=0, max_hp   = this->gstate->get_HP(this_p_index);
            for(auto &strategy : this->strategies){
                score += strategy->test(BUF_INDEX_1);
                std::cout << "exploit\n";
                this->simu_othersTurn_for(this_p_index, BUF_INDEX_2);
                std::cout << "exploit\n";
                score -= (max_hp - this->gstate->get_HP(this_p_index));
                if(score > maxScore){
                    maxScore = score;
                    this->bestStrategy_index[BUF_INDEX_1] = i;
                }
                i++;
                this->backup(BUF_INDEX_1);
                std::cout << "score = " << score << std::endl;
                score = 16000;
            }
        }

        if(this->strategies[this->bestStrategy_index[BUF_INDEX_1]]->apply(BUF_INDEX_1) == -1){
            this->ngine->registerTarget((char)PASS);
            std::cout << "COUCOU" << std::endl;
        }
    }


    void DeepAI::backup(int buf_infex){
        while(this->cmdCount[buf_infex]){
            this->ngine->undo();
            this->cmdCount[buf_infex]--;
        }
    }

    inline void DeepAI::incCmdCount(int count, int buf_infex){
        this->cmdCount[buf_infex] += count;
    }

    void DeepAI::simu_othersTurn_for (char actu_p_index, int buf_infex){
        char curr;
        this->ngine->registerTarget((char)SIMU_PASS);
        this->ngine->execute();
        this->incCmdCount(1,BUF_INDEX_1);
        std::cout << "others\n";
        curr = this->gstate->getActualPlayerIndex();
        while ((curr != actu_p_index) && this->gstate->get_HP(actu_p_index)){ 
            std::cout << "others\n";
            this->simu_bestStrategyFor_curr();
            this->strategies[this->bestStrategy_index[BUF_INDEX_2]]->apply(BUF_INDEX_2);
            this->ngine->registerTarget((char)SIMU_PASS);
            this->ngine->execute();
            this->incCmdCount(1,BUF_INDEX_1);
            curr = this->gstate->getActualPlayerIndex();
        }
    }

    int DeepAI::simu_bestStrategyFor_curr (){
        int score, maxScore = 0;
        int i=0;
        for(auto &strategy : this->strategies){
            score = strategy->test(BUF_INDEX_2);
            if(score > maxScore){
                maxScore = score;
                this->bestStrategy_index[BUF_INDEX_2] = i;
            }
            i++;
            this->backup(BUF_INDEX_2);
        }
    }


    DeepAI::~DeepAI(){}

    
}