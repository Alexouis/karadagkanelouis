/*
 * File             Animation.cpp
 * Directory        render
 * Created Date     Tuesday, December 7th 2021, 3:09:50 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include "AnimatedObject.h"

namespace render{
    AnimatedObject::AnimatedObject(){
        this->mSprite.setTexture(frames);
        this->mCurrentFrame = 0;
        
    }
};