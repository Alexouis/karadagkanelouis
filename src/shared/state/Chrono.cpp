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

#include "State.h"
#include "Chrono.h"
#include <unistd.h>
#include <csignal>
#include <iostream>

namespace state{

    Chrono::Chrono (){
    }
    Chrono::~Chrono (){

    }
    void Chrono::bind (int sigNum){
        signal(sigNum, &Chrono::handler);
    }
    void Chrono::handler (int){
        State::chronoCount--;
        if(State::chronoCount){
            alarm(State::chronoStep);
        }
    }
    void Chrono::start (char chronoStep, char ChronoCount) {
        State::chronoStep = chronoStep;
        State::chronoCount = ChronoCount;
        alarm(State::chronoStep);
    }
}