
#include <boost/test/unit_test.hpp>


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>

#include <iostream>
#include <fstream>
#include <math.h>

#include "tmx/MapLoader.h"
//#include <SFML/Graphics/RenderTexture.hpp>

#include <sstream>
#include <string>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <thread>
#include <state.h>
#include <engine.h>
#include <render.h>
#include <ai.h>

#include <json/json.h>

#include <unistd.h>
#include <csignal>
#include <utility>
BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

using namespace state;
using namespace engine;
using namespace render;

BOOST_AUTO_TEST_CASE(testenumstate)
{
  
    
    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int> {});

    std::vector<Attack> attacks;

    struct Attack strike;

    strike.name=STRIKE;
    strike.type=CONTACT;
    strike.damage=20;
    strike.range=1;

    struct Attack powerfulStrike;

    powerfulStrike.name=POWERFULSTRIKE;
    powerfulStrike.type=CONTACT;
    powerfulStrike.damage=80;
    powerfulStrike.range=2;

    attacks.push_back(strike);
    attacks.push_back(powerfulStrike);

    BOOST_CHECK_EQUAL(attacks[0].name,STRIKE);
    BOOST_CHECK_EQUAL(attacks[0].type,CONTACT);
    BOOST_CHECK_EQUAL(attacks[0].damage,20);
    BOOST_CHECK_EQUAL(attacks[0].range,1);
    BOOST_CHECK_EQUAL(attacks[1].name,POWERFULSTRIKE);
    BOOST_CHECK_EQUAL(attacks[1].type,CONTACT);
    BOOST_CHECK_EQUAL(attacks[1].damage,80);
    BOOST_CHECK_EQUAL(attacks[1].range,2);

    std::vector<std::vector<MapTile>> gameMap;

    struct MapTile grass;

    grass.type=GRASS;
    grass.state=FREE;

    struct MapTile house;

    house.type=HOUSE;
    house.state=OBSTACLE; 
    

}
BOOST_AUTO_TEST_CASE(test_Position)
{
    //Test Position
    Position pos(1,9);

    BOOST_CHECK_EQUAL(pos.x,1);
    BOOST_CHECK_EQUAL(pos.y,9);

}
BOOST_AUTO_TEST_CASE(test_Stats)
{
    //Test Stats
    Stats stat{};
    stat.setAp(5);
    stat.setAttack(30);
    stat.setHp(200);
    stat.setMp(4);
    stat.setShield(40);
    stat.resetPoints(HERO,60);
    stat.resetPoints(DEMON,60);

    BOOST_CHECK_EQUAL(stat.getAp(),8);
    BOOST_CHECK_EQUAL(stat.getAttack(),30);
    BOOST_CHECK_EQUAL(stat.getHp(),200);
    BOOST_CHECK_EQUAL(stat.getMp(),7);
    BOOST_CHECK_EQUAL(stat.getShield(),40);
}
BOOST_AUTO_TEST_CASE(test_Player)
{   
    //Test Player

    Stats stat{};
    stat.setAp(5);
    stat.setAttack(30);
    stat.setHp(200);
    stat.setMp(4);
    stat.setShield(40);
    
    Position pos(1,9);
    
    Player erza{};
    erza.resetPoints();
    Player valla("hahaha",DEMON,Position(3,5),1,user);
    valla.move(Position(2,5));
    valla.move(2,5);
    valla.setPosXY(5,8);
    BOOST_CHECK_EQUAL(valla.getPosition().x,5);
    BOOST_CHECK_EQUAL(valla.getPosition().y,8);
    erza.init();
    int x=erza.getLevel();
    
    erza.setName("Erza");
    BOOST_CHECK_EQUAL(erza.getName(),"Erza");

    
    erza.setPClass(HERO);
    
    erza.setStats(Stats(5,1));

    BOOST_CHECK_EQUAL(erza.getPClass(),HERO);

    erza.setLevel(10);
    BOOST_CHECK_EQUAL(erza.getLevel(),10);

    erza.setOrientation(NORTH);
    BOOST_CHECK_EQUAL(erza.getOrientation(),NORTH);
    erza.setOrientation(SOUTH);
    BOOST_CHECK_EQUAL(erza.getOrientation(),SOUTH);
    erza.setOrientation(EAST);
    BOOST_CHECK_EQUAL(erza.getOrientation(),EAST);
    erza.setOrientation(WEST);
    BOOST_CHECK_EQUAL(erza.getOrientation(),WEST);

    erza.setStatus(PLAYING);
    BOOST_CHECK_EQUAL(erza.getStatus(),PLAYING);
    erza.pass();
    BOOST_CHECK_EQUAL(erza.getStatus(),WAITING);
    erza.setStatus(PLAYING);
    BOOST_CHECK_EQUAL(erza.getStatus(),PLAYING);
    erza.setStatus(WAITING);
    BOOST_CHECK_EQUAL(erza.getStatus(),WAITING);
    erza.setStatus(DEAD);
    BOOST_CHECK_EQUAL(erza.getStatus(),DEAD);

    erza.setStats(stat);
    BOOST_CHECK_EQUAL(erza.getStats().getHp(),200);
    BOOST_CHECK_EQUAL(erza.getStats().getMp(),4);
    BOOST_CHECK_EQUAL(erza.getStats().getAp(),5);
    BOOST_CHECK_EQUAL(erza.getStats().getShield(),40);
    BOOST_CHECK_EQUAL(erza.getStats().getAttack(),30);

    erza.setPosition(pos);
    BOOST_CHECK_EQUAL(erza.getPosition().x,1);
    BOOST_CHECK_EQUAL(erza.getPosition().y,9);
    std::vector<Attack> attack_list;
    Attack hit;
    hit.damage=10000;
    hit.cost = 5;
    Attack fire;
    Attack shot;
    attack_list.push_back(hit);
    attack_list.push_back(fire);
    attack_list.push_back(shot);

    erza.setAttacks(attack_list);
    valla.setAttacks(erza.getAttacks());

    stat.setHp(100);
    stat.setAp(10);
    erza.setStats(stat);
    valla.setStats(stat);
    std::unique_ptr<Player> target = std::unique_ptr<Player>(new Player());
    target->setStats(stat);
    
    Player ai{};
    ai.setInput(deep_ai);
    BOOST_CHECK_EQUAL(ai.getInput(), deep_ai);

    //  faire attaquer
    BOOST_CHECK_EQUAL(target->getStats().getHp(),100);
    char mmm = 0;
    valla.setCurrentAttackIndex(mmm);
    BOOST_CHECK_EQUAL(valla.getCurrentAttackIndex(),mmm);
    valla.attack(target);
    BOOST_CHECK_EQUAL(target->getStats().getHp(),0);

    valla.setAp(10);
    valla.setMp(10);
    valla.setHp(100);
    Attack a = valla.getAttack(0);
    Position poss;
    poss.operator!=(valla.getPosition());
    poss.operator+(valla.getPosition());
    poss.operator==(valla.getPosition());
    
    //Chrono test

}
    //State test
BOOST_AUTO_TEST_CASE(test_State)
{
    //State gameState;
  //  State gameState{2000,1000};
    State gameState(22,22);
    int old_ap_thp[2];
    gameState.pull_AP_THP(9, 10, old_ap_thp);
    auto gstate = std::shared_ptr<state::State>(&gameState);
    auto args = std::unique_ptr<Action_Args>(new Action_Args(gstate, 9, 10, old_ap_thp));
    args->p_index = gameState.getActualPlayerIndex();
    //(2000,1000);
    gameState.init();
    gameState.initPlayer();
    gameState.initPositions();
   // gameState->State->initPlayer();
    gameState.initMap();
    gameState.isDead(0);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).x,10);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).y,10);
    //gameState.makeMove(args);
    Action::move(args);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).x,9);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).y,10);
    gameState.passTurn(0);
    Action::move(args);
    BOOST_CHECK_EQUAL(gameState.getActualPlayerIndex(),1);
    gameState.passTurn(1);
    BOOST_CHECK_EQUAL(gameState.getActualPlayerIndex(),0);
    gameState.cancel_passTurn(1);
    BOOST_CHECK_EQUAL(gameState.getActualPlayerIndex(),1);
    gameState.passTurn(0);
    
    BOOST_CHECK_EQUAL(gameState.getActualPlayerIndex(),0);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).x,9);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).y,10);
    gameState.passTurn(1);
    BOOST_CHECK_EQUAL(gameState.getActualPlayerIndex(),1);
    gameState.setCurrPlayerAttack(0);
    gameState.setCurrPlayerAttack(1);
   // gameState.cancel_select(0);
   gameState.cancel_select(args);
    gameState.getPlayerStats(1).setAttack(10000);
    gameState.getPlayerStats(0).setAttack(10000);
    gameState.getCurrAttackIndex(0);
    gameState.getAttackIndex(0);
  ///////  gameState.makeAttackOn(9,10);
    int tgt[2] = {9,10};
    int aptt[2];
  ///////  gameState.cancel_attack(tgt,aptt);
    gameState.cancel_attack(args);
    gameState.cancel_passTurn(1);
    //gameState.makeAttack(args);
    Action::attack(args);
    auto a = gameState.getPlayerClass(0);
    BOOST_CHECK_EQUAL(gameState.getPlayersCount(),2);
    gameState.passTurn(0);
    BOOST_CHECK(gameState.isAI_Now());
    int target [2];
    char closest_enemy_index= gameState.closestEnemyIndexTo(1,target);
    char weakest_enemy_index= gameState.weakestEnemyIndexTo(1,target);
    char strngest_enemy_index= gameState.strngestEnemyIndexTo(1,target);
    char enemyWithLessHp= gameState.enemyWithLessHp_Of(1,target);
    char enemyWithLessMp= gameState.enemyWithLessMp_Of(1,target);
    struct Attack att;
    
    int dmg = gameState.damage(0,1,att);
    Player valla{};
    Stats d = valla.getStats();
    gameState.simu_attack(0,1,0,d,d);
    Position depart(10,6);
    Position dest(5,5);
    bool path = gameState.BFS_Shortest_Path(depart,dest);
    valla.move(dest);
   /////// int prevpos[3];
  ///////  gameState.cancel_move(prevpos);
    gameState.cancel_move(args);
    gameState.chronoStart(1,1);
    std::map<std::string,state::Stats> plStat = gameState.getPlayerStats();
    std::vector<ID> plId = gameState.getPlayersID();
    std::map<std::string,std::vector<Attack>> vectAttack = gameState.getPlayersAttacks();
    int mp = gameState.get_MP(0);
    int aap = gameState.get_AP(0);
    int ap[2];
    int hp = gameState.get_HP(0);
    bool yes = gameState.hasEnough_AP(0,0);
    gameState.pull_AP_THP(9,10,ap);
    gameState.pull_AP_THP(9,17,ap);
    gameState.turn_in_AI(0);
    gameState.turn_all_in_AI();
    gameState.restore_user(0);
    gameState.restore_all_users();
    gameState.lock();
    //gameState.unlock();
    gameState.lock();
    gameState.endGame();
    bool gover = gameState.getGameOver();
    gameState.setGameOver(gover);
    gameState.setGameOver(true);
    BOOST_CHECK(gameState.getGameOver());

    ///////////////////////////////////////////////////
    
}

BOOST_AUTO_TEST_CASE(test_Engine)
{
    
    State gameState(22,22);
    gameState.init();
    gameState.initPlayer();
    gameState.initPositions();
   // gameState->State->initPlayer();
    gameState.initMap();
    gameState.isDead(0);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).x,10);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).y,10);
 ////////// //  gameState.moveCurrentPlayer(9,10);
 //////////  std::unique_ptr<engine::Action_Args> move = ;
  //////////  gameState.makeMove();
  /////////////  BOOST_CHECK_EQUAL(gameState.playerPosition(0).x,9);
  /////////////  BOOST_CHECK_EQUAL(gameState.playerPosition(0).y,10);
    gameState.passTurn(0);
    BOOST_CHECK_EQUAL(gameState.getActualPlayerIndex(),1);
    gameState.setCurrPlayerAttack(0);
    gameState.getPlayerStats(1).setAttack(10000);
  ////////// // gameState.makeAttackOn(9,10);
    
   // gameState.lock();
    //gameState.unlock();
    
     render::GameWindow gamewindow;
     engine::Engine ngine;
     //gameState.connect(ngine);
//     ngine.start();
//     ai::AI g_ai;
//     std::unique_ptr<engine::Command> cmdHolder;
//     //void(*action[2])(std::unique_ptr<Action_Args>&) iii;
//     //std::unique_ptr<Action_Args>& args;
//     //engine::Command com();
//     std::shared_ptr<state::State> gstate;
//     state::Position old_pos;
//     int old_ap_thp[2];
//     engine::Action_Args ac_args1(gstate,1,1,old_pos,2);
//     engine::Action_Args ac_args2(gstate,1,1,old_ap_thp);
//     engine::Action_Args ac_args3(gstate,1,1);
//     engine::Action_Args ac_args4(&ngine,1);

//    // engine::Action ac1;
//     std::unique_ptr<Action_Args> args =std::unique_ptr<Action_Args>(new Action_Args(gstate,1,1,old_ap_thp));
    
//     //args = std::unique_ptr<Action_Args(gstate,1,1,old_ap_thp)>;
//     Action::doNothing(args);
//     Action::move(args);
    
    //Engine ngin{};
   // ngin.start();
  //  ngin.stop();
 //   ngin.Start();
    

}

/* vim: set sw=2 sts=2 et : */
