
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>

#include  <state.h>


BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

using namespace state;

BOOST_AUTO_TEST_CASE(TestSFML)
{
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
    BOOST_CHECK_EQUAL(attacks[1].damage,855);
    BOOST_CHECK_EQUAL(attacks[1].range,2);

    std::vector<std::vector<MapTile>> gameMap;

    struct MapTile grass;

    grass.type=GRASS;
    grass.state=FREE;

    struct MapTile house;

    house.type=HOUSE;
    house.state=OBSTACLE; 
    



    //Test Position
    Position pos(1,9);

    BOOST_CHECK_EQUAL(pos.x,1);
    BOOST_CHECK_EQUAL(pos.y,9);



    //Test Stats
    Stats stat{};
    stat.setAp(5);
    stat.setAttack(30);
    stat.setHp(200);
    stat.setMp(4);
    stat.setShield(40);
    stat.resetPoints(HERO,60);
    stat.resetPoints(DEMON,60);

    BOOST_CHECK_EQUAL(stat.getAp(),5);
    BOOST_CHECK_EQUAL(stat.getAttack(),30);
    BOOST_CHECK_EQUAL(stat.getHp(),200);
    BOOST_CHECK_EQUAL(stat.getMp(),4);
    BOOST_CHECK_EQUAL(stat.getShield(),40);
    
    //Test Player
    Player erza{};
    erza.resetPoints();
    Player valla("hahaha",DEMON,Position(3,5),1,0);
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

    BOOST_CHECK(erza.getPlaying());

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
    hit.damage=10;
    hit.cost = 5;
    Attack fire;
    Attack shot;
    attacks.push_back(hit);
    attacks.push_back(fire);
    attacks.push_back(shot);

    erza.setAttacks(attack_list);
    valla.setAttacks(erza.getAttacks());
    
    stat.setHp(100);
    stat.setAp(10);
    erza.setStats(stat);
    valla.setStats(stat);

    std::unique_ptr<Player> target{};
    target->setStats(stat);
    
    Player ai{};
    ai.setIsAI(true);

    //  faire attaquer
    BOOST_CHECK_EQUAL(target->getStats().getHp(),100);
    char mmm = 0;
    valla.setCurrentAttackIndex(mmm);
    BOOST_CHECK_EQUAL(valla.getCurrentAttackIndex(),mmm);
    valla.attack(target);
    BOOST_CHECK_EQUAL(target->getStats().getHp(),90);


    //Chrono test

    Chrono krono{};
    krono.handler(5);


    //State test

    State gameState(2000,1000);
    gameState.init();
    gameState.initPlayer();
    gameState.initMap();
    gameState.isDead(0);
    gameState.passTurn();
    gameState.endGame();
    bool gover = gameState.getGameOver();
    gameState.setGameOver(gover);
    gameState.setGameOver(false);
    BOOST_CHECK_EQUAL(gameState.getGameOver(),false);

    ///////////////////////////////////////////////////
    










  }  
}

/* vim: set sw=2 sts=2 et : */
