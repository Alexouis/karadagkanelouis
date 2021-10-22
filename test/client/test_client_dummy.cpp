
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>

#include  "Player.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestSFML)
{
  {
    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int> {});

    Player::Player erza{"Elsa",DEMON,pos,5};
  }
}

/* vim: set sw=2 sts=2 et : */
