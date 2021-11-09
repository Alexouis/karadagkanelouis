#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
    if (!texture.loadFromFile("../../res/synthetic grass/ground_grass_gen_07.png"))
    {
        // error...
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.draw(sprite);
}

// Fin test SFML

#include  <state.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    Exemple exemple;
    exemple.setX(53);
    //testSFML();
    sf::Texture texture;
    if (!texture.loadFromFile("/home/mkas/ENSEA/karadagkanelouis/res/grass/grass5.png")){
        // error...
        cout << "no texture! " << endl; 
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;      while (window.pollEvent(event))      {          if (event.type == sf::Event::Closed)              window.close();      }

        window.clear();
        //window.draw(shape);
        window.draw(sprite);
        window.display();
    }
//
    //MapLoader::MapLoader("res/map");
    cout << "It works !" << endl;

}
