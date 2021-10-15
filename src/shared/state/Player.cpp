#include "Player.h"

namespace state {
    Player::Player(){};

    Player::Player(std::string name, char playerClass, Position position, char level){
        Player::name = name;
        Player::playerClass = playerClass;
        Player::position = position;
        Player::level = level;
    }

    void Player::init (){

    };
    
    void Player::attack(std::string chosenAttack, Position aim){

    };

    void Player::pass (){

    };

    void Player::move (Position destination){

    };

    const std::string& Player::getName() const{
        return Player::name;
    };

    void Player::setName(const std::string& name){
        Player::name = name;
    };

    char Player::getPlayerClass() const{
        return Player::playerClass;
    };

    void Player::setPlayerClass(char playerClass){
        Player::playerClass = playerClass;
    };

    const Position& Player::getPosition() const{
        return Player::position;
    };

    void Player::setPosition(const Position& position){
        Player::position = position;
    };

    char Player::getOrientation() const{
        return Player::orientation;
    };

    void Player::setOrientation(char orientation){
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

    char Player::getLevel() const{
        return Player::level;
    };



    Player::~Player(){};
};
