
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>

#include  <state.h>


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

using namespace state;
using namespace engine;

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
    gameState.makeMove(args);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).x,9);
    BOOST_CHECK_EQUAL(gameState.playerPosition(0).y,10);
    gameState.passTurn(0);
    BOOST_CHECK_EQUAL(gameState.getActualPlayerIndex(),1);
    gameState.setCurrPlayerAttack(0);
    gameState.getPlayerStats(1).setAttack(10000);
    gameState.makeAttack(args);
    auto a = gameState.getPlayerClass(0);
    BOOST_CHECK_EQUAL(gameState.getPlayersCount(),2);
    BOOST_CHECK(gameState.isAI_Now());
    int target [2];
    char closest_enemy_index= gameState.closestEnemyIndexTo(1,target);
    char weakest_enemy_index= gameState.weakestEnemyIndexTo(1,target);
    gameState.chronoStart(1,1);
    std::map<std::string,state::Stats> plStat = gameState.getPlayerStats();
    std::vector<ID> plId = gameState.getPlayersID();
    std::map<std::string,std::vector<Attack>> vectAttack = gameState.getPlayersAttacks();


    gameState.lock();
    //gameState.unlock();
    gameState.endGame();
    bool gover = gameState.getGameOver();
    gameState.setGameOver(gover);
    gameState.setGameOver(true);
    BOOST_CHECK(gameState.getGameOver());

    ///////////////////////////////////////////////////
    
}

BOOST_AUTO_TEST_CASE(test_Engine)
{
    Engine ngin{};
   // ngin.start();
  //  ngin.stop();
 //   ngin.Start();


}

/* vim: set sw=2 sts=2 et : */
