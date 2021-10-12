#include <boost/test/unit_test.hpp>
#include "Player.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestPlayer)
{
    Player pl ("Erza",HERO,Position(0,1),1);

    BOOST_CHECK_EQUAL(pl.getName(),"Erza");
    BOOST_CHECK_EQUAL(pl.getPlayerClass(),HERO);
    BOOST_CHECK_EQUAL(pl.getPosition(),Position(0,1));
    BOOST_CHECK_EQUAL(pl.getLevel(),1);

}