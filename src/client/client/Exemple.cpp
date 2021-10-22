#include <state/Exemple.h>  // Included from library shared_static
#include "Exemple.h"
#include "state/Player.h"
#include <iostream>

using namespace std;

namespace client {

    void Exemple::setX (int x) {
        // Create an object from "shared" library
        state::Exemple y {};
        y.setX(x);

        this->x = x;

        state::Player p{};
        p.setName("baba");

        cout<< p.getName();
    }

}

