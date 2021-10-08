#include "Stats.h"

namespace state
{
    Stats::Stats(){};

    Stats::Stats(char playerClass, char level){

    };

    // Setters and Getters

    int Stats::getAttack() const{
        return Stats::attack;
    };

    void Stats::setAttack(int attack){
        Stats::attack=attack;
    };

    int Stats::getShield() const{
        return Stats::shield;
    };

    void Stats::setShield(int shield){
        Stats::shield=shield;
    };

    int Stats::getHp() const{
        return Stats::hp;
    };

    void Stats::setHp(int hp){
        Stats::hp=hp;
    };

    char Stats::getAp() const{
        return Stats::ap;
    };

    void Stats::setAp(char ap){
        Stats::ap=ap;
    };

    char Stats::getMp() const{
        return Stats::mp;
    };

    void Stats::setMp(char mp){
        Stats::mp=mp;
    };

    Stats::~Stats(){

    };

} // namespace state
