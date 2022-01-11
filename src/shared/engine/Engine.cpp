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
#include <iostream> 

#define CODE_MASK(X)   ((   X & 0x70 ) >> 4 )  //return code
#define CODE_ACTION(X) (((  X & 0x10 ) >> 4 ) | ((  X & 0x20 ) >> 5 )) //to knw if move or attack
#define VALUE_MASK(X)  (    X & 0xF  )         //return value
#define ACTION(X)      ((   X & 0xF0 ) >> 7 )  //return targetCode

#define SPELL1 0x0 //[targetCode code value] =  [0 000 0000]
#define SPELL2 0x1 //[targetCode code value] =  [0 000 0001]
#define SPELL3 0x2 //[targetCode code value] =  [0 000 0010]
#define SPELL4 0x3 //[targetCode code value] =  [0 000 0011]
#define SPELL5 0x4 //[targetCode code value] =  [0 000 0100]
#define MENU 0x10  //[targetCode code value] =  [0 001 0000]
#define PASS 0x20  //[targetCode code value] =  [0 010 0000]
#define START 0x30  //[code value] =  [0011 0000]


namespace engine{
    Engine::Engine(){
        this->action.reserve(2);
        this->selection.reserve(4);
        
        this->action[1] = &Action::move;
        this->action[0] = &Action::attack;

        this->selection[0] = &Action::select;
        this->selection[1] = &Action::doNothing;
        this->selection[2] = &Action::passTurn;
        this->selection[3] = &Action::startGame;
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
                this->qcmd.front()->action(cmdHolder->args);
                this->qcmd.pop();
            }
        }
        this->cmdHolder.release();
    }

    void Engine::addCommand(std::unique_ptr<Command>& cmd){
        this->qcmd.push(std::move(cmd));
    }

    void Engine::execute(){
        if(!this->qcmd.empty()){
            this->qcmd.front()->action(this->qcmd.front()->args);
            this->cmdHistory.push(std::move(this->qcmd.front()));
            this->qcmd.pop();
            return;
        }
        if(Engine::timeOut()){
            this->currentState->passTurn();
        }
    }

    void Engine::execute(std::unique_ptr<Command>& cmd){
        cmd->action(cmd->args);
        this->cmdHistory.push(std::move(cmd));
        this->currentState->lock();
    }

    void Engine::setState(std::shared_ptr<state::State>& gState){
        this->currentState = gState;
        this->currentState->connect(this);
    }

    void Engine::registerTarget (int x, int y, char selected){
        if(ACTION(selected)){
            std::unique_ptr<Action_Args> args = std::unique_ptr<Action_Args>(new Action_Args(this->currentState, x, y));
            this->cmdHolder = std::unique_ptr<Command>(new Command(this->action[CODE_ACTION(this->selected)], args));
            this->qcmd.push(std::move(cmdHolder));
            this->selected = selected;
        }
        else{
            this->registerTarget(selected);
            this->execute();
        }
    }

    void Engine::registerTarget (char selected){
        this->selected = selected;
        std::unique_ptr<Action_Args> args = std::unique_ptr<Action_Args>(new Action_Args(this->currentState, VALUE_MASK(selected)));
        this->cmdHolder = std::unique_ptr<Command>(new Command(this->selection[CODE_MASK(selected)], args));
        this->qcmd.push(std::move(cmdHolder));
    }

    bool Engine::isActionFromAI (){
        return this->currentState->isAI_Now();
    }

    bool Engine::timeOut(){
        return (!state::State::chronoCount);
    }

    void Engine::bind (ai::AI* g_ai){
        g_ai->bind(this, this->currentState);
    }


    void Engine::undo(){
        if(!this->cmdHistory.empty()){
            this->cmdUndid.push_back(std::move(this->cmdHistory.top()));
            this->cmdHistory.pop();
        }
    }

    void Engine::redo(){
        if(!this->cmdUndid.empty()){
            this->cmdHistory.push(std::move(this->cmdUndid.back()));
            this->cmdUndid.pop_back();
        }
    }

    Engine::~Engine (){}
}