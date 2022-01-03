/*
 * File             AI.cpp
 * Directory        ai
 * Created Date     Wednesday, December 29th 2021, 11:35:20 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "AI.h"
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
    AI::AI (){
        this->initSrand ();
        this->selected = 6;
        this->selections[0] = (char)SPELL1; // attack selection
        this->selections[1] = (char)SPELL2; // attack selection
        this->selections[2] = (char)SPELL3; // attack selection
        this->selections[3] = (char)SPELL4; // attack selection
        this->selections[4] = (char)SPELL5; // attack selection
        this->selections[5] = (char)MOVE;   // move instead of pass turn : AI never passes turn
        this->selections[6] = (char)MOVE;   // move
    }
    AI::~AI (){

    }

    void AI::chooseAction (){
        this->selected = (char)this->getRandValBetween(0,6);
        if(this->selections[this->selected] == (char)MOVE){
            state::Position p = this->gstate->playerPosition(this->gstate->getActualPlayerIndex());
            this->targetX = p.getX();
            this->targetY = p.getY();
            int x = rand() % 2;
            if(x){
                float dx = 2*(rand() % 2) -1;
                this->targetX += dx;
            }else{
                float dy = 2*(rand() % 2) -1;
                this->targetY += dy;
            }
        }
    }
    void AI::registerActionTo (engine::Engine* ngine){
        ngine->registerTarget(this->targetX, this->targetY, this->selections[this->selected]);
    }
    void AI::initSrand (){
        srand (time(NULL));
    }
    inline int AI::getRandValBetween (int a, int b){
        return ((rand() % (b-a+1)) +a);
    }
    void AI::bindState (std::shared_ptr<state::State>& gstate){
        this->gstate = gstate;
    }
    char AI::closestEnemyIndexTo (char p_index, int* pos){
        return this->gstate->closestEnemyIndexTo(p_index, pos);
    }
    char AI::weakestEnemyIndexTo (char p_index, int* pos){
        return this->gstate->weakestEnemyIndexTo(p_index, pos);
    }
}