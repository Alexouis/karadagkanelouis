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

namespace engine{

    Chrono::Chrono (){

    }
    Chrono::~Chrono (){

    }
    void Chrono::bind (int sigNum){
        signal(sigNum, handler);
    }
    void Chrono::handler (int){

    }
    void Chrono::start (int count){
        alarm(count);
    }
}