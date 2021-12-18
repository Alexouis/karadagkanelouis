#include "State.h"
#include <functional>

namespace state {
    /*
    The State class corresponds to the state of the entire game
    
    */
    State::State (int mapWidth, int mapHeight){
        MapTile tile;
        tile.state = FREE;
        tile.type  = GRASS;
        for(unsigned int i = 0; i < mapWidth; i++){
            for(unsigned int j = 0; j < mapHeight; j++){
                this->gameMap[j][i] = tile;
            }
            
        }
    };
    void State::init (){
        this->turn = 0;
        this->actualPlayerIndex = 0;
        this->chronoCount = 60; //60 seconds
        this->gameOver = false;
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
    char State::getChronoCount() const{
        return this->chronoCount;
    };
    void State::setChronoCount(char chronoCount){
        this->chronoCount= chronoCount;
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
    void State::makeAttackOn (int targetX, int targetY){
        char st = this->gameMap[targetY][targetX].state;
        if(st == OCCUPIED){
            std::string attackerId = this->players_id[this->actualPlayerIndex];
            std::string taregtId = this->gameMap[targetY][targetX].player_id;
            (this->players[attackerId.back()][attackerId])->attack(this->players[taregtId.back()][taregtId]);
        }
    };
    void State::moveCurrentPlayer (int dstX, int dstY){
        std::string id = this->players_id[this->actualPlayerIndex];
        Position prevPos = (this->players[id.back()][id])->getPosition();
        this->gameMap[prevPos.getY()][prevPos.getX()].state = FREE;
        this->gameMap[dstY][dstX].player_id = id;
        this->players[id.back()][id]->move(dstX,dstY);
        this->gameMap[dstY][dstX].state = OCCUPIED;
        this->gameMap[dstY][dstX].player_id = id;
    };
    Position State::playerPosition (char playerIndex) {
        std::string id = this->players_id[playerIndex];
        return (this->players[id.back()][id])->getPosition();
    };

};
