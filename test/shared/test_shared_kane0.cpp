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
    
    //Test Player
    Player erza{};
    
    //State test
    State s(22,22);

    std::vector<std::string> player_id;
    player_id.push_back("erza");

    int turn = 0;
    char actualPlayerIndex = 25;
    
    s.setActualPlayerIndex(actualPlayerIndex);
    //s.setPlayers_id(player_id);
    s.setTurn(turn);

    BOOST_CHECK_EQUAL(s.getActualPlayerIndex(), actualPlayerIndex);

    //BOOST_CHECK_EQUAL(s.getPlayers_id()[0], player_id[0]);
    BOOST_CHECK_EQUAL(s.getTurn(), turn);
    s.incrementTurn();
    BOOST_CHECK_EQUAL(s.getTurn(), turn+1);
    

    erza.setName("Erza");
    BOOST_CHECK_EQUAL(erza.getName(),"Erza");

    erza.setPClass(HERO);
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

    erza.setPlaying(true);
    BOOST_CHECK(erza.getPlaying());


    
  }
}

/* vim: set sw=2 sts=2 et : */
