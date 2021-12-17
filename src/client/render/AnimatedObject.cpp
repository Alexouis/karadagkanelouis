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

#define SPRITE_SCALE 5.f

namespace render{
    AnimatedObject::AnimatedObject(sf::Texture & frames){
        this->mSprite.setTexture(frames);
        this->mCurrentFrame = 0;
        
    };

    void AnimatedObject::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(this->mSprite, states);
        
    };

    void AnimatedObject::update (sf::Time dt, Json::Value framesInfos, std::string frameKey, sf::Vector2f positions){
        this->mSprite.setTextureRect(sf::IntRect(435, 520, 50, 60));
        this->mSprite.setPosition(positions.x,positions.y);
        this->mSprite.scale(sf::Vector2f(SPRITE_SCALE,SPRITE_SCALE)); 
         
    };


    const sf::Sprite& AnimatedObject::getMSprite() const{
        return this->mSprite;
    };

    void AnimatedObject::setMSprite(const sf::Sprite& mSprite){

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

};