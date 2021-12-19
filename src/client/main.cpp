
#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>

#include <iostream>
#include <fstream>
#include <math.h>

#include "tmx/MapLoader.h"
//#include <SFML/Graphics/RenderTexture.hpp>

#include <render.h>
#include <sstream>
#include <string>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


// Fin test SFML
#include <thread>
#include <state.h>
#include <engine.h>
#include <json/json.h>

using namespace std;
using namespace state;
using namespace render;



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


 void renderMap(void){

    GameWindow gamewindow;

    while(gamewindow.window.isOpen()){

        sf::Event event;

        while(gamewindow.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gamewindow.window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            if(event.type == sf::Event::MouseButtonPressed){
            }
        }

        gamewindow.update();
        gamewindow.window.clear();
        gamewindow.draw();
        gamewindow.window.display();

    }

    
} 


 void engineExplo(void){

    GameWindow gamewindow;
    engine::Engine ngine;
    std::unique_ptr<engine::Command> cmdHolder;
    gamewindow.shareStateWith(ngine);
    //ngine.start();

    bool debug = false;

    while(gamewindow.window.isOpen()){

        sf::Event event;

        sf::Vector2f mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Mouse::getPosition(gamewindow.window));
        sf::Vector2f mousePosWorld = gamewindow.screenToWorld(mousePosScreen);
        while(gamewindow.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gamewindow.window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
                debug = !debug;
            if(event.type == sf::Event::MouseButtonPressed){
                
                cmdHolder = std::unique_ptr<engine::Command>(new engine::Move((int)mousePosWorld.x, (int)mousePosWorld.y));
                ngine.execute(cmdHolder);
            }
        }

        gamewindow.update();
        gamewindow.window.clear();
        gamewindow.draw();
        gamewindow.window.display();

    }

    
} 

int main(int argc,char* argv[])
{

    //GameWindow gw;


    if(argc < 2){
        std::cout << "Expected one argument like 'client' or 'render'" << std::endl;
        return 0;
    }

    if(strcmp(argv[1], "client") == 0){
        testSFML();
    }
    else if(strcmp(argv[1], "render") == 0){
        renderMap();
    }
    }else if(strcmp(argv[1], "randomMap") == 0){
        randomMap();
    }
    else{
        std::cout << "Expected one argument like 'client' or 'render'" << std::endl;
    }

    return 0;

}
