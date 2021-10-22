#include "State.h"

namespace state {

    State::State (){

    };
    void State::init (){

    };
    void State::initPlayer (char index){

    };
    void State::initMap (char index){

    };
    bool State::isDead (){
        //return State::gameOver;
    };
    void State::passTurn (){

    };
    void State::incrementTurn (){
        State::turn++;
    };
    void State::endGame (){
        State::gameOver = true;
    };
    void State::initPositions (){
        //efter
    };
    State::~State (){

    };
    // Setters and Getters
    const std::vector<std::vector<MapTile>>& State::getGameMap() const{
        return State::gameMap;
    };
    void State::setGameMap(const std::vector<std::vector<MapTile>>& gameMap){
        State::gameMap = gameMap;
    };
    const std::map<std::string,Player>& State::getHeroes() const{

    };
    void State::setHeroes(const std::map<std::string,Player>& heroes){

    };
    const std::map<std::string,Player>& State::getEnemies() const{

    };
    void State::setEnemies(const std::map<std::string,Player>& enemies){

    };
    int State::getTurn() const{
        return State::turn;
    };
    void State::setTurn(int turn){
        State::turn = turn;
    };
    char State::getPlaying() const{
        return State::playing;
    };
    void State::setPlaying(char playing){
        State::playing = playing;
    };
    char State::getTimeLeft() const{
        return State::timeLeft;
    };
    void State::setTimeLeft(char timeLeft){
        State::timeLeft= timeLeft;
    };
    const std::vector<std::string>& State::getPlayer_id() const{
        return State::player_id;
    };
    void State::setPlayer_id(const std::vector<std::string>& player_id){
        State::player_id = player_id;
    };
    bool State::getGameOver() const{
        return State::gameOver;
    };
    void State::setGameOver(bool gameOver){
        State::gameOver = gameOver;
    };

};
