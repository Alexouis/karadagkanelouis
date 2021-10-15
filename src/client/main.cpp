#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <map>
#include <memory>
#include <unistd.h>
#include <thread>
//#include <microhttpd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <state.h>
#include "client.h"



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

<<<<<<< HEAD
    state::Player p{};
    
    //const string name = "Erza";
    //Position position{1,2};
    //Player player{};
    //player.setName("Alex"); 
=======
    Position pos;
    pos.setX(12);

    cout << pos.getX() << endl;
>>>>>>> 6e0998b1c3e460cec29a6dd6c7c1b4650f8ef02a

    return 0;
}
