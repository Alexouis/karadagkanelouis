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

#include "engine.h"

namespace engine{
    Engine::Engine(state::State& gstate){
        this->currentState = &gstate;
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
                this->cmdHolder = std::move(this->qcmd.front());
                this->qcmd.pop();
                this->cmdHolder->action(this->currentState);
            }
        }
        this->cmdHolder.release();
    }

    void Engine::addCommand(std::unique_ptr<Command>& cmd){
        this->qcmd.push(std::move(cmd));
    }
}