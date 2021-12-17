/*
 * File             CommandExecutor.cpp
 * Directory        engine
 * Created Date     Thursday, December 16th 2021, 10:17:19 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

 #include "CommandExecutor.h"

namespace engine{

    CommandExecutor::CommandExecutor(state::State& gstate){
        this->gstate = &gstate;
    }
    
    void CommandExecutor::start(){
        this->mThread = std::thread(&CommandExecutor::run, this);
        if(this->mThread.joinable()){ 
            this->mThread.join(); 
        }
    }

    void CommandExecutor::run(){
        while(!this->gstate->getGameOver()){
            if(!this->qcmd->empty()){
                this->cmdHolder = std::move(this->qcmd->front());
                this->qcmd->pop();
                this->cmdHolder->action(this->gstate);
            }
        }
        this->cmdHolder.release();
    }

}