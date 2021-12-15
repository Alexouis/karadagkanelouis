#include "Stats.h"
#include <map>
#include <string>


namespace state
{
    //Par défaut, si on ne précise pas la classe et le niveau du joueur, il est créé avec des statistiques réduites comparées à celles offertes par les classes.
    Stats::Stats(){
        attack = 10;
        shield = 10;
        hp = 50;
        mp = 3;
        ap = 3;
    }; 

    Stats::Stats(char playerClass, char level){

        std::map<std::string, char> coeffStats;

        switch(playerClass)
        {
            case HERO:
                coeffStats["attack"] = 25 ;
                coeffStats["shield"] = 25 ;
                coeffStats["hp"] = 80 ;
                coeffStats["mp"] = 3 ;
                coeffStats["ap"] = 6 ;
                break;

            case DEMON:
                coeffStats["attack"] = 30 ;
                coeffStats["shield"] = 20 ;
                coeffStats["hp"] = 70 ;
                coeffStats["mp"] = 4 ;
                coeffStats["ap"] = 6 ;
                break;

            default:
                coeffStats["attack"] = 10 ;
                coeffStats["shield"] = 10 ;
                coeffStats["hp"] = 50 ;
                coeffStats["mp"] = 3 ;
                coeffStats["ap"] = 3 ;
                break;
        }

        attack = coeffStats["attack"]*level*0.8;
        shield = coeffStats["shield"]*level*0.8;
        hp = coeffStats["hp"]*level;
        mp = coeffStats["mp"]+level/20;
        ap = coeffStats["ap"]+level/30;
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
