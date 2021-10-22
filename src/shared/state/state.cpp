#include "State.h"

namespace state {

    State::State (){

    };
    void State::init (){

    };
    void State::initPlayer (char index){
        
    };
    void State::initMap (){

    };
    bool State::isDead (Player p){
        return (p.getStatus() == DEAD);
    };
    void State::passTurn (){
        this->playing++;
    };
    void State::incrementTurn (){
        this->turn++;
    };
    void State::endGame (){
        this->gameOver = true;
    };
    void State::initPositions (){
        //efter
    };
    State::~State (){

    };
    // Setters and Getters
    const std::vector<std::vector<MapTile>>& State::getGameMap() const{
        return this->gameMap;
    };
    void State::setGameMap(const std::vector<std::vector<MapTile>>& gameMap){
        this->gameMap = gameMap;
    };
    const std::map<std::string,Player>& State::getHeroes() const{
        return this->heroes;
    };
    void State::setHeroes(const std::map<std::string,Player>& heroes){
        this->heroes = heroes;
    };
    const std::map<std::string,Player>& State::getEnemies() const{
        return this->enemies;
    };
    void State::setEnemies(const std::map<std::string,Player>& enemies){
        this->enemies = enemies;
    };
    int State::getTurn() const{
        return this->turn;
    };
    void State::setTurn(int turn){
        this->turn = turn;
    };
    char State::getPlaying() const{
        return this->playing;
    };
    void State::setPlaying(char playing){
        this->playing = playing;
    };
    char State::getTimeLeft() const{
        return this->timeLeft;
    };
    void State::setTimeLeft(char timeLeft){
        this->timeLeft= timeLeft;
    };
    const std::vector<std::string>& State::getPlayer_id() const{
        return State::player_id;
    };
    void State::setPlayer_id(const std::vector<std::string>& player_id){
        this->player_id = player_id;
    };
    bool State::getGameOver() const{
        return this->gameOver;
    };
    void State::setGameOver(bool gameOver){
        this->gameOver = gameOver;
    };

};
