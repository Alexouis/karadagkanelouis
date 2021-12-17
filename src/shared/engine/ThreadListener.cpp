/*
 * File             ThreadListener.cpp
 * Directory        engine
 * Created Date     Friday, December 17th 2021, 2:55:05 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "ThreadListener.h"
#include <functional>
#include "Move.h"
#include "Attack.h"

namespace engine{
    ThreadListener::ThreadListener (Event& event, Mouse& mouse, Window& window) {
        this->event = &event;
        this->mouse = &mouse;
        this->window = &window;
    }

    void ThreadListener::start(){
        this->mThread = std::thread(&ThreadListener::run, this);
        if(this->mThread.joinable()){ 
            this->mThread.join(); 
        }
    }

    void ThreadListener::run(){
        while(this->window->isOpen){
            while(this->window->pollEvent){
                if(this->event->type == EventType::Closed){
                    this->window->isOpen = false;
                }
                if(this->event->type == EventType::KeyPressed && this->event->keyCode == 'D'){
                }
                if(this->event->type == EventType::MouseButtonPressed){
                    this->cmdHolder = std::unique_ptr<Command>(new Move(this->mouse->posX, this->mouse->posY));
                    this->qcmd->push(std::move(this->cmdHolder));
                }

            }
        }
    }

}