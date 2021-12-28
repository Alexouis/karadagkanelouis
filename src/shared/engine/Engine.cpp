/*
 * File             Engine.cpp
 * Directory        engine
 * Created Date     Friday, December 17th 2021, 8:09:49 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */
#include <iostream>
#include "engine.h"

#define CODE_MASk(X)  ((X & 0xF0) >> 4)
#define VALUE_MASK(X) ( X & 0xF )
#define IS_MOVE(X)    ((X & 0xF0) >> 7)

#define SPELL1 0x0 //[code value] =  [0000 0000]
#define SPELL2 0x1 //[code value] =  [0000 0001]
#define SPELL3 0x2 //[code value] =  [0000 0010]
#define SPELL4 0x3 //[code value] =  [0000 0011]
#define SPELL5 0x4 //[code value] =  [0000 0100]
#define MENU 0x10  //[code value] =  [0001 0000]
#define PASS 0x20  //[code value] =  [0010 0000]

namespace engine{
    Engine::Engine(){
        this->action.reserve(2);
        this->selection.reserve(3);
        
        this->action[1] = &Action::move;
        this->action[0] = &Action::attack;

        this->selection[0] = &Action::select;
        this->selection[1] = &Action::doNothing;
        this->selection[2] = &Action::passTurn;
    }


    void Engine::start(){
        this->eThread = std::thread(&Engine::run, this);
        if(this->eThread.joinable()){ 
            this->eThread.join(); 
        }
    }


    void Engine::stop(){
        this->fuel = false;
    }


    void Engine::run(){
        while(!this->currentState->getGameOver()){
            if(!this->qcmd.empty()){
                this->qcmd.front()->action(this->currentState, cmdHolder->x, cmdHolder->y);
                this->qcmd.pop();
            }
        }
        this->cmdHolder.release();
    }

    void Engine::addCommand(std::unique_ptr<Command>& cmd){
        this->qcmd.push(std::move(cmd));
    }

    void Engine::execute(std::unique_ptr<Command>& cmd){
        cmd->action(this->currentState, cmd->x, cmd->y);
    }

    void Engine::setState(std::shared_ptr<state::State>& gState){
        this->currentState = gState;
    }

    void Engine::registerTarget (int x, int y, char selected){
        if(IS_MOVE(selected)){
            this->cmdHolder = std::unique_ptr<Command>(new Command(this->action[CODE_MASk(this->selected)], x, y));
            this->qcmd.push(std::move(cmdHolder));
            this->selected = selected;
        }
        
    }

    void Engine::registerTarget (char selected){
        this->selected = selected;
        this->cmdHolder = std::unique_ptr<Command>(new Command(this->selection[CODE_MASk(selected)], VALUE_MASK(selected), 0));
        this->qcmd.push(std::move(cmdHolder));
    }

    Engine::~Engine (){}
}