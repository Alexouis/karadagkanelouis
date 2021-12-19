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
#include <iostream>
#include "tmx/MapLoader.h"

#define SPRITE_SCALE 5.f

namespace render{
    AnimatedObject::AnimatedObject(sf::Texture & frames){
        this->mSprite.setTexture(frames);
        sf::IntRect rect =  this->mSprite.getTextureRect();
        this->mCurrentFrame = 0;        
    };

    void AnimatedObject::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(this->mSprite, states);        
    };

    void AnimatedObject::update (sf::Time dt, Json::Value framesInfos, std::string frameKey, sf::Vector2f positions){
        
        int i_x=framesInfos[frameKey]["w"].asInt()*mCurrentFrame;
        int i_y=framesInfos[frameKey]["y_offset"].asInt();
        int scale_x=framesInfos[frameKey]["w"].asInt();
        int scale_y=framesInfos[frameKey]["h"].asInt();

        this->mSprite.setTextureRect(sf::IntRect(i_x, i_y, scale_x, scale_y));
        this->mSprite.scale(sf::Vector2f(SPRITE_SCALE,SPRITE_SCALE));
    };


    const sf::Sprite& AnimatedObject::getMSprite() const{
        return this->mSprite;
    };

    void AnimatedObject::setMSprite(const sf::Sprite& mSprite){
        this->mSprite = mSprite;
    };

    const std::size_t& AnimatedObject::getMCurrentFrame() const{
        return this->mCurrentFrame;
    };
    void AnimatedObject::setMCurrentFrame(const std::size_t& mCurrentFrame){
        this->mCurrentFrame=mCurrentFrame;
    };
    const sf::Time& AnimatedObject::getMElapasedTime() const{
        return this->mElapasedTime;
    };
    void AnimatedObject::setMElapasedTime(const sf::Time& mElapasedTime){
        this->mElapasedTime=mElapasedTime;
    };
    bool AnimatedObject::getMRepeat() const{
        return this->mRepeat;
    };
    void AnimatedObject::setMRepeat(bool mRepeat){
        this->mRepeat=mRepeat;
    };
    AnimatedObject::~AnimatedObject(){

    };
};