/*
 * File             Command.cpp
 * Directory        engine
 * Created Date     Monday, December 13th 2021, 3:21:34 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "Command.h"

namespace engine{
   Command::Command (void(*action)(std::shared_ptr<state::State>&, int, int), int x, int y){
      this->x = x;
      this->y = y;
      this->action = action;
   }


   Command::~Command (){
   }
};