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
    bool ai::AI::test = true;
    AI::AI (){
        this->selected = 6;
        this->selections[0] = (char)SPELL1; // attack selection
        this->selections[1] = (char)SPELL2; // attack selection
        this->selections[2] = (char)SPELL3; // attack selection
        this->selections[3] = (char)SPELL4; // attack selection
        this->selections[4] = (char)SPELL5; // attack selection
        this->selections[5] = (char)MOVE;   // move instead of pass turn : AI never passes turn
        this->selections[6] = (char)MOVE;   // move
    }
    AI::AI (engine::Engine* ngine) {
            this->selected = 6;
            this->selections[0] = (char)SPELL1; // attack selection
            this->selections[1] = (char)SPELL2; // attack selection
            this->selections[2] = (char)SPELL3; // attack selection
            this->selections[3] = (char)SPELL4; // attack selection
            this->selections[4] = (char)SPELL5; // attack selection
            this->selections[5] = (char)MOVE;   // move instead of pass turn : AI never passes turn
            this->selections[6] = (char)MOVE;
            ngine->bind(this);
        }

    AI::~AI (){

    }

    /*  permet de simuler l’action que l’IA a choisi d’effectuer comme le fait de cliquer sur un bouton 
    ou sur la map par exemple. */
    void AI::exploit (){
        this->selected = (char)this->getRandValBetween(0,6);
        if(this->selections[this->selected] == (char)MOVE){
            state::Position p = this->gstate->playerPosition(this->gstate->getActualPlayerIndex());
            this->targetX = p.x;
            this->targetY = p.y;
            int x = rand() % 2;
            if(x){
                float dx = 2*(rand() % 2) -1;
                this->targetX += dx;
            }else{
                float dy = 2*(rand() % 2) -1;
                this->targetY += dy;
            }
        }
        this->ngine->registerTarget(this->targetX, this->targetY, this->selections[this->selected]);
    }

    void AI::set_mode_analysis (){
        this->analysis = true;
    }
    void AI::set_mode_execute (){
        this->analysis = false;
    }
    bool AI::mode_analysis (){
        return this->analysis;
    }

    //  Reçoit le code du bouton associé à l'indice passé en paramètre de la fonction.
    char AI::getSelection (char sel){
        return this->selections[sel];
    }
    
    //  Permet de démarrer le générateur de nombre aléatoire.
    void AI::initSrand (){
        srand (time(NULL));
    }

    //  Retourne de manière aléatoire un entier entre un intervalle passé en argument.
    inline int AI::getRandValBetween (int a, int b){
        return ((rand() % (b-a+1)) +a);
    }

    //  Permet partager le state ainsi que l’engine aux IA.
    void AI::bind (engine::Engine* ngine, std::shared_ptr<state::State>& gstate){
        this->ngine  = std::shared_ptr<engine::Engine>(ngine);
        this->gstate = gstate;
        std::cout << "ok state = " << (int)this->gstate->getActualPlayerIndex() << std::endl;
    }

    //  Renvoie l’index de l’ennemi le plus proche.
    char AI::closestEnemyIndexTo (char p_index, int* pos){
        return this->gstate->closestEnemyIndexTo(p_index, pos);
    }

    //  Renvoie l’index de l’ennemi le plus faible.
    char AI::weakestEnemyIndexTo (char p_index, int* pos){
        return this->gstate->weakestEnemyIndexTo(p_index, pos);
    }

    //  Renvoie l’index de l’ennemi ayant le moins de HP.
    char AI::enemyWithLessHp_Of (char p_index, int* pos){
        return this->gstate->enemyWithLessHp_Of(p_index, pos);
    }

    //  Renvoie l’index de l’ennemi ayant le moins de MP.
    char AI::enemyWithLessMp_Of (char p_index, int* pos){
        return this->gstate->enemyWithLessMp_Of(p_index, pos);
    }

    //  Permet de mesurer le temps entre deux actions successives de l’IA.
    inline float AI::action_dt (){
        return (this->action_time_end.tv_sec - this->action_time_ini.tv_sec + (float)(this->action_time_end.tv_nsec - this->action_time_ini.tv_nsec)/1000000.f);
    }
}