#include "State.h"
#include <functional>
#include <iostream>
#include <cstdlib>

namespace state {
    /*
    The State class corresponds to the state of the entire game
    
    */
    char state::State::chronoCount = 10;
    char state::State::chronoStep = 1;
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
        auto player = std::unique_ptr<Player>(new Player("goku",DEMON, Position(10,10), 1, false));
        ID p_id;
        p_id.id = player->getName();
        p_id.id.push_back('0');
        p_id.next = 1;
        p_id.prev = 1;
        this->players_id.push_back(p_id);

        this->players[0] = new std::map<std::string, std::unique_ptr<Player>>;
        this->players[1] = new std::map<std::string, std::unique_ptr<Player>>;
        this->players[p_id.id.back()-'0'][0][p_id.id] = std::move(player);

        this->gameMap[10][10].state = OCCUPIED;
        this->gameMap[10][10].player_index = 0;

        player = std::unique_ptr<Player>(new Player("buu",HERO, Position(11,11), 1, true));
        p_id.id = player->getName();
        p_id.id.push_back('1');
        p_id.next = 0;
        p_id.prev = 0;
        this->players_id.push_back(p_id);
        this->players[p_id.id.back()-'0'][0][p_id.id] = std::move(player);

        
        this->gameMap[11][11].state = OCCUPIED;
        this->gameMap[11][11].player_index = 1;

        
    };
    void State::init (){
        this->turn = 0;
        this->playersCount = 2;
        this->actualPlayerIndex = 0;
        this->gameOver = false;
    };
    void State::initPlayer (){

    };
    void State::initMap (){

    };
    bool State::isDead (char p_index){
        std::string id = this->players_id[p_index].id;
        return (this->players[id.back()-'0']->find(id)->second->getStatus() == DEAD);
    };
    void State::passTurn (){
        this->actualPlayerIndex = this->players_id[this->actualPlayerIndex].next;
        this->ngine->chrono->start(1,10);
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
    bool State::getGameOver() const{
        return this->gameOver;
    };
    void State::setGameOver(bool gameOver){
        this->gameOver = gameOver;
    };
    void State::makeAttackOn (int targetX, int targetY){
        char st = this->gameMap[targetY][targetX].state;
        if(st == OCCUPIED){
            std::string attackerId = this->players_id[this->actualPlayerIndex].id;
            std::string taregtId = this->players_id[this->gameMap[targetY][targetX].player_index].id;
            this->players[attackerId.back()-'0']->find(attackerId)->second->attack(this->players[taregtId.back()-'0']->find(taregtId)->second);
        }
    };
    void State::moveCurrentPlayer (int dstX, int dstY){
        if((dstX >= 0 && dstY >= 0) && (dstX < this->gameMap.size() && dstY < this->gameMap.size())){
            std::string id = this->players_id[this->actualPlayerIndex].id;
            Position prevPos = this->players[id.back()-'0']->find(id)->second->getPosition();
            this->gameMap[prevPos.getY()][prevPos.getX()].state = FREE;
            this->gameMap[dstY][dstX].player_index = this->actualPlayerIndex;
            this->players[id.back()-'0']->find(id)->second->move(dstX,dstY);
            this->gameMap[dstY][dstX].state = OCCUPIED;
        }
    };
    Position State::playerPosition (char playerIndex) {
        std::string id = this->players_id[playerIndex].id;
        return this->players[id.back()-'0']->find(id)->second->getPosition();
    };
    state::playerClass State::getPlayerClass (char playerIndex) {
        const std::string id = this->players_id[playerIndex].id;
        return this->players[id.back()-'0']->find(id)->second->getPClass();
    }

    char  State::getPlayersCount () const{
        return this->playersCount;
    }

    void State::setCurrPlayerAttack (char attackIndex){
        const std::string id = this->players_id[this->actualPlayerIndex].id;
        this->players[id.back()-'0']->find(id)->second->setCurrentAttackIndex(attackIndex);
    }

    void State::lock(){
        this->padlock = true;
    }

    void State::unlock(){
        this->padlock = false;
    }

    bool State::isAI_Now(){
        const std::string id = this->players_id[this->actualPlayerIndex].id;
        return this->players[id.back()-'0']->find(id)->second->getIsAI();
    }

    void State::connect (engine::Engine* ngine){
        this->ngine = ngine;
    }

    char State::closestEnemyIndexTo (char p_index){
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        Position source = this->players[id->id.back()-'0']->find(id->id)->second->getPosition();
        Position target;
        char found;
        int d = 0, min = 2*this->gameMap.size();

        for(auto const& enemy : *(this->players[enemies])){
            target = enemy.second->getPosition();
            d = abs(target.getX() - source.getX()) + abs(target.getY() - source.getY());
            if(d < min){
                min = d;
                found = this->gameMap[target.getX()][target.getY()].player_index;
            }
        }
        return found;
    }
    char State::weakestEnemyIndexTo (char p_index){
        Player p;
        p.getLevel();
        ID *id = &this->players_id[p_index];
        char enemies = !(id->id.back()-'0');
        char found, level, weakest = 100;

        for(auto const& enemy : *(this->players[enemies])){
            level = enemy.second->getLevel();
            if(level < weakest){
                weakest = level;
                found = this->gameMap[enemy.second->getPosition().getX()][enemy.second->getPosition().getY()].player_index;
            }
        }
        return found;
    }
};
