#include "State.h"
#include <functional>
#include <iostream>

namespace state {
    /*
    The State class corresponds to the state of the entire game
    
    */
    State::State (int mapWidth, int mapHeight){
        this->init();

        MapTile tile;
        tile.state = FREE;
        tile.type  = GRASS;
        this->gameMap.resize(mapHeight);

        for(unsigned int i = 0; i < mapWidth; i++){
            for(unsigned int j = 0; j < mapHeight; j++){
                this->gameMap[j].push_back(tile);
            }
        }

        this->players.resize(this->playersCount);
        auto player = std::unique_ptr<Player>(new Player("goku",DEMON, Position(10,10), 1, true));
        std::string playerId = player->getName();
        playerId.push_back('0');
        this->players_id.push_back(playerId);

        this->players[0] = new std::map<std::string, std::unique_ptr<Player>>;
        this->players[1] = new std::map<std::string, std::unique_ptr<Player>>;
        this->players[playerId.back()-'0'][0][playerId] = std::move(player);

        this->gameMap[10][10].state = OCCUPIED;
        this->gameMap[10][10].player_id = playerId;

        player = std::unique_ptr<Player>(new Player("buu",HERO, Position(11,11), 1, true));
        playerId = player->getName();
        playerId.push_back('1');
        this->players_id.push_back(playerId);
        this->players[playerId.back()-'0'][0][playerId] = std::move(player);

        
        this->gameMap[11][11].state = OCCUPIED;
        this->gameMap[11][11].player_id = playerId;

        
    };
    void State::init (){
        this->turn = 0;
        this->playersCount = 2;
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
            this->players[attackerId.back()-'0']->find(attackerId)->second->attack(this->players[taregtId.back()-'0']->find(taregtId)->second);
        }
    };
    void State::moveCurrentPlayer (int dstX, int dstY){
        std::string id = this->players_id[this->actualPlayerIndex];
        Position prevPos = this->players[id.back()-'0']->find(id)->second->getPosition();
        this->gameMap[prevPos.getY()][prevPos.getX()].state = FREE;
        this->gameMap[dstY][dstX].player_id = id;
        this->players[id.back()-'0']->find(id)->second->move(dstX,dstY);
        this->gameMap[dstY][dstX].state = OCCUPIED;
        this->gameMap[dstY][dstX].player_id = id;
    };
    Position State::playerPosition (char playerIndex) {
        std::string id = this->players_id[playerIndex];
        return this->players[id.back()-'0']->find(id)->second->getPosition();
    };
    state::playerClass State::getPlayerClass (char playerIndex) {
        const std::string id = this->players_id[playerIndex];
        return this->players[id.back()-'0']->find(id)->second->getPClass();
    }

    char  State::getPlayersCount () const{
        return this->playersCount;
    }
};
