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

namespace ai{
    DeepAI::DeepAI(){
        this->strategies[0] = std::unique_ptr<Attack_Strongest    >(new Attack_Strongest    (this));
        this->strategies[1] = std::unique_ptr<Attack_Closest      >(new Attack_Closest      (this));
        this->strategies[2] = std::unique_ptr<Attack_Weakest      >(new Attack_Weakest      (this));
        this->strategies[3] = std::unique_ptr<Attack_Most_InDanger>(new Attack_Most_InDanger(this));
    }

    void DeepAI::exploit(){
        if(this->mode == ANALYSIS){
            this->gstate->turn_all_in_AI();
            int score, maxScore = 0;
            for(int i=0; auto &strategy : this->strategies){
                score = strategy->test(this->gstate, this->ngine);
                if(score > maxScore){
                    maxScore = score;
                    this->bestStrategy_index = i;
                }
                i++;
                this->backup();
            }

            this->strategies[this->bestStrategy_index]->work(this->gstate, this->ngine);
        }
    }

    void DeepAI::backup(){
        while(this->cmdCount){
            this->ngine->undo();
            this->cmdCount--;
        }
    }

    inline void DeepAI::incCmdCount(int count){
        this->cmdCount += count;
    }
    DeepAI::~DeepAI(){}

    
}