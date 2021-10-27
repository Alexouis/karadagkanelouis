#include "State.h"

namespace state {
    /*
    The State class corresponds to the state of the entire game
    
    */
    State::State (){

    };
    void State::init (){

    };
    void State::initPlayer (){
        
    };
    void State::initMap (){

    };
    bool State::isDead (Player p){
        return (p.getStatus() == DEAD);
    };
    void State::passTurn (){
        this->actualPlayerIndex++;
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
    const std::map<std::string,Player*>& State::getHeroes() const{
        return this->heroes;
    };
    void State::setHeroes(const std::map<std::string,Player*>& heroes){
        this->heroes = heroes;
    };
    const std::map<std::string,Player*>& State::getEnemies() const{
        return this->enemies;
    };
    void State::setEnemies(const std::map<std::string,Player*>& enemies){
        this->enemies = enemies;
    };
    int State::getTurn() const{
        return this->turn;
    };
    void State::setTurn(int turn){
        this->turn = turn;
    };
    // get the index of the actual player
    char State::getActualPlayerIndex() const{
        return this->actualPlayerIndex;
    };
    void State::setActualPlayerIndex(char actualPlayerIndex){
        this->actualPlayerIndex = actualPlayerIndex;
    };
    char State::getTimeLeft() const{
        return this->timeLeft;
    };
    void State::setTimeLeft(char timeLeft){
        this->timeLeft= timeLeft;
    };
    //get the player 
    const std::vector<std::string>& State::getPlayers_id() const{
        return this->players_id;
    };
    void State::setPlayers_id(const std::vector<std::string>& player_id){
        this->players_id = player_id;
    };
    bool State::getGameOver() const{
        return this->gameOver;
    };
    void State::setGameOver(bool gameOver){
        this->gameOver = gameOver;
    };

};
