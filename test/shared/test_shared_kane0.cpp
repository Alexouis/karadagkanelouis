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

    //Test Position
    Position pos{};
    pos.setX(1);
    pos.setY(9);



    //Test Stats
    Stats stat{};
    stat.setAp(5);
    stat.setAttack(30);
    stat.setHp(200);
    stat.setMp(4);
    stat.setShield(40);
    
    //Test Player
    Player erza{};
    
    //State test
    State s{};

    std::vector<std::string> player_id;
    player_id.push_back("erza");

    int turn = 0;
    char playing = 25;
    char timeLeft = 25;

    s.setHeroes({{"erza",&erza}});
    s.setPlaying(playing);
    s.setPlayer_id(player_id);
    s.setTurn(turn);
    s.setTimeLeft(timeLeft);

    BOOST_CHECK_EQUAL(s.getPlaying(), playing);

    BOOST_CHECK_EQUAL(s.getPlayer_id()[0], player_id[0]);
    BOOST_CHECK_EQUAL(s.getTurn(), turn);
    BOOST_CHECK_EQUAL(s.getTimeLeft(), timeLeft);
    s.incrementTurn();
    BOOST_CHECK_EQUAL(s.getTurn(), turn+1);
    

    erza.setName("Erza");
    BOOST_CHECK_EQUAL(erza.getName(),"Erza");

    erza.setPlayerClass(HERO);
    BOOST_CHECK_EQUAL(erza.getPlayerClass(),HERO);

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

    erza.setPlaying(true);
    BOOST_CHECK(erza.getPlaying());
    
    erza.setStatus(PLAYING);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getStatus(),PLAYING);
    erza.setStatus(WAITING);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getStatus(),WAITING);
    erza.setStatus(DEAD);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getStatus(),DEAD);
    BOOST_CHECK_EQUAL(s.isDead(*s.getHeroes().find("erza")->second), true);
    
    erza.setStats(stat);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getStats().getHp(),200);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getStats().getMp(),4);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getStats().getAp(),5);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getStats().getShield(),40);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getStats().getAttack(),30);

    erza.setPosition(pos);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getPosition().getX(),1);
    BOOST_CHECK_EQUAL(s.getHeroes().find("erza")->second->getPosition().getY(),9);


    
  }
}

/* vim: set sw=2 sts=2 et : */