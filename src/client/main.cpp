#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include  <state.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    Exemple exemple;
    exemple.setX(53);

    cout << "It works !" << endl;

    Position pos;
    pos.setX(12);

    cout << pos.getX() << endl;

    return 0;
}
