/*
 * File             HeuristicAI.cpp
 * Directory        ai
 * Created Date     Monday, January 3rd 2022, 9:55:46 am
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2022  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "HeuristicAI.h"
#include <iostream>

#define SPELL1 0x0 //[targetCode code value] =  [0 000 0000]
#define SPELL2 0x1 //[targetCode code value] =  [0 000 0001]
#define SPELL3 0x2 //[targetCode code value] =  [0 000 0010]
#define SPELL4 0x3 //[targetCode code value] =  [0 000 0011]
#define SPELL5 0x4 //[targetCode code value] =  [0 000 0100]
#define MENU 0x10  //[targetCode code value] =  [0 001 0000]
#define PASS 0x20  //[targetCode code value] =  [0 010 0000]
#define MOVE 0x90  //[targetCode code value] =  [1 001 0000]

namespace ai{

    HeuristicAI::~HeuristicAI (){

    }
    void HeuristicAI::exploit (){
        this->selected = (char)MOVE;
        int target[2];
        char targetIndex = this->closestEnemyIndexTo(this->gstate->getActualPlayerIndex(), target);
        state::Position source = this->gstate->playerPosition(this->gstate->getActualPlayerIndex());
        state::Stats st = this->gstate->getPlayerStats(this->gstate->getActualPlayerIndex());
        if(st.getMp()){
            int x = rand() % 2;
            int deltaX = target[0] - source.getX();
            int deltaY = target[1] - source.getY();
            int sx = (deltaX > 0) - (deltaX < 0);
            int sy = (deltaY > 0) - (deltaY < 0);
            int mx = sx * (std::min(abs(deltaX) - ( !sy ), (int)st.getMp()) - ( !!sy ) * ( !!sx ) * x);
            int my = sy * (std::min(abs(deltaY) - ( !sx ), (int)st.getMp() - abs(mx)) - ( !!sy ) * ( !!sx ) * ( !x ));
            this->targetX = source.getX() + mx;
            this->targetY = source.getY() + my;
            this->ngine->registerTarget(this->targetX, this->targetY, this->selected);
        }
        if(st.getAp()){
            this->selected = (char)getRandValBetween(0,4);
            this->ngine->registerTarget(this->targetX, this->targetY, this->getSelection(this->selected));
            this->ngine->registerTarget(target[0], target[1], (char)MOVE);
        }
    }
}