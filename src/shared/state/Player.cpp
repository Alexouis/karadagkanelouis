#include "Player.h"
#include <vector>

namespace state {
    Player::Player(){
        name = "player";
        pClass = HERO;
        position.setX(0);
        position.setY(0);
        level = 1;
        orientation = WEST;
        isAI = false;
        playing = false;
        status = WAITING;
        stats = Stats(pClass,level);
        struct Attack punch;
        punch.name=STRIKE;
        punch.type=CONTACT;
        punch.damage = 10;
        punch.range = 1;
        punch.cost = 2;

        attacks.push_back(punch);
    };

    Player::Player(std::string name, playerClass pClass, Position position, char level, bool isAI){
        Player::name = name;
        Player::pClass = pClass;
        Player::position = position;
        Player::level = level;
        Player::orientation = orientation;
        Player::isAI = isAI;

        playing = false;
        status = WAITING;
        stats = Stats(pClass,level);

        switch(pClass)
        {
            case HERO:
                struct Attack shoot;
                shoot.name=SHOOT;
                shoot.type=DISTANCE;
                shoot.damage = 20;
                shoot.range = 5;
                shoot.cost = 2;

                struct Attack powerfulShoot;
                powerfulShoot.name=POWERFULSHOOT;
                powerfulShoot.type=DISTANCE;
                powerfulShoot.damage = 45;
                powerfulShoot.range = 2;
                powerfulShoot.cost = 5;

                attacks.push_back(shoot);
                attacks.push_back(powerfulShoot);
                break;
            
            case DEMON:
                struct Attack strike;
                strike.name=STRIKE;
                strike.type=CONTACT;
                strike.damage = 20;
                strike.range = 2;
                strike.cost = 3;

                struct Attack powerfulStrike;
                powerfulStrike.name=POWERFULSTRIKE;
                powerfulStrike.type=CONTACT;
                powerfulStrike.damage = 50;
                powerfulStrike.range = 1;
                powerfulStrike.cost = 6;

                attacks.push_back(strike);
                attacks.push_back(powerfulStrike);
                break;

            default:
                struct Attack hit;
                hit.name=STRIKE;
                hit.type=CONTACT;
                hit.damage = 10;
                hit.range = 1;
                hit.cost = 2;

                attacks.push_back(hit);
                break;
        }
    }

    void Player::init (){
        name = "player";
        pClass = HERO;
        position.setX(0);
        position.setY(0);
        level = 1;
        orientation = WEST;
        isAI = false;
        playing = false;
        status = WAITING;
        stats = Stats(pClass,level);
        struct Attack punch;
        punch.name=STRIKE;
        punch.type=CONTACT;
        punch.damage = 10;
        punch.range = 1;
        punch.cost = 2;

        attacks.push_back(punch);
    };
    
    void Player::attack(std::unique_ptr<Player>& player){
        bool can_attack = stats.getAp() >= this->attacks[this->currentAttackIndex].cost;
        if(can_attack) 
        {
            this->stats.setAp(stats.getAp()-this->attacks[this->currentAttackIndex].cost);
            player->stats.setHp(player->stats.getShield()+player->stats.getHp()-this->attacks[this->currentAttackIndex].damage-this->stats.getAttack());
        }
    };

    void Player::pass (){
        playing = false;
        status = WAITING;
    };

    void Player::move (Position destination){
        Player::position.setX(destination.getX());
        Player::position.setY(destination.getY());
    };

    void Player::move (int x, int y){
        Player::position.setX(x);
        Player::position.setY(y);
    };

    const std::string& Player::getName() const{
        return Player::name;
    };

    void Player::setName(const std::string& name){
        Player::name = name;
    };

    playerClass Player::getPClass() const{
        return Player::pClass;
    };

    void Player::setPClass(playerClass pClass){
        Player::pClass = pClass;
    };

    const Position& Player::getPosition() const{
        return Player::position;
    };

    void Player::setPosition(const Position& position){
        Player::position = position;
    };

    void Player::setPosXY(int x, int y){
        Player::position.setX(x);
        Player::position.setY(y);
    };

    char Player::getOrientation() const{
        return Player::orientation;
    };

    void Player::setOrientation(char playerOrientation){
        Player::orientation = orientation;
    };

    bool Player::getPlaying() const{
        return Player::playing;
    };

    void Player::setPlaying(bool playing){
        Player::playing = playing;
    };

    const std::vector<Attack>& Player::getAttacks() const{
        return Player::attacks;
    };

    void Player::setAttacks(const std::vector<Attack>& attacks){
        Player::attacks = attacks;
    };

    const Stats& Player::getStats() const{
        return Player::stats;
    };/* 
 */
    void Player::setStats(const Stats& stats){
        Player::stats = stats;
    };

    playerStatus Player::getStatus() const{
        return Player::status;
    };

    void Player::setStatus(playerStatus status){
        Player::status = status;
    };

    void Player::setLevel(char level){
        Player::level = level;
    };

    char Player::getLevel() const{
        return Player::level;
    };

    char Player::getCurrentAttackIndex() const{
        return this->currentAttackIndex;
    };
    void Player::setCurrentAttackIndex(char currentAttackIndex){
        this->currentAttackIndex = currentAttackIndex;
    };

    bool Player::getIsAI() const{
        return this->isAI;
    };

    void Player::setIsAI(bool isAI){
        this->isAI = isAI;
    };
    

    Player::~Player(){};
};
