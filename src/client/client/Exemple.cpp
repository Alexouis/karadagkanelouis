#include <state/Exemple.h>  // Included from library shared_static
#include "Exemple.h"
#include "state/Player.h"


namespace client {

void Exemple::setX (int x) {
    // Create an object from "shared" library
    state::Exemple y {};
    y.setX(x);

    this->x = x;
}

void Player::setName (std::string name) {
    // Create an object from "shared" library
    state::Exemple y {};
    y.setX(x);

    this->x = x;
}


}

