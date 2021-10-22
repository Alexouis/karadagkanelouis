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

    //Test Position
    Position pos{5,5};

    return 0;

    //Test Player
    Player erza{"Elsa",DEMON,pos,5};
    
    pos.setX(1);
    pos.setY(1);

    erza.setName("Erza");
    erza.setPlayerClass(HERO);
    erza.setPosition(pos);
    erza.setLevel(10);

    if (erza.getName() == "Erza" && erza.getPosition().getX() == 1 && erza.getPlayerClass()==HERO && erza.getLevel()==10)
    {
        cout << "Test Player: OK !" << endl;
    }

    
}
