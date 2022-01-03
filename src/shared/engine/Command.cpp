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
#include <iostream>

namespace engine{
   Command::Command (void(*action)(std::unique_ptr<Action_Args>&) , std::unique_ptr<Action_Args>& args){
      this->args = std::move(args);
      this->action = action;
   }


   Command::~Command (){
   }
};