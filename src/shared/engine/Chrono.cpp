/*
 * File             Chrono.cpp
 * Directory        engine
 * Created Date     Sunday, December 19th 2021, 10:55:55 am
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Chrono.h"
#include <unistd.h>
#include <csignal>
#include <iostream>

namespace engine{

    Chrono::Chrono (){
    }
    Chrono::~Chrono (){

    }
    void Chrono::bind (int sigNum){
        signal(sigNum, &Chrono::handler);
    }
    void Chrono::handler (int){
        state::State::chronoCount--;
        std::cout << "hand\n";
        if(state::State::chronoCount){
            alarm(state::State::chronoStep);
        }
    }
    void Chrono::start (char chronoStep, char ChronoCount) {
        state::State::chronoStep = chronoStep;
        state::State::chronoCount = ChronoCount;
        std::cout << "start\n";
        alarm(state::State::chronoStep);
    }
}