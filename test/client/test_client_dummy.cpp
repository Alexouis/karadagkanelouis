
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>

#include <state.h>

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestSFML)
{
  {
    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int> {});

    vector<Attack> attacks;

    struct Attack strike;

    strike.name=STRIKE;
    strike.type=CONTACT;
    strike.damage=20;
    strike.range=1;

    struct Attack powerfulStrike;

    powerfulStrike.name=POWERFULSTRIKE;
    powerfulStrike.type=CONTACT;
    powerfulStrike.damage=80;
    powerfulstrike.range=2;

    attacks.push_back(strike);
    attacks.push_back(powerfulStrike);

    //Test Position
    Position pos{5,5};

    return 0;
    
    //Test Player
    Player erza{};

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


    BOOST_CHECK_EQUAL(erza.getPlaying(),false);



  }
}

/* vim: set sw=2 sts=2 et : */
