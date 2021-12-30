
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

#include <sstream>
#include <string>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


// Fin test SFML
#include <thread>
#include <state.h>
#include <engine.h>
#include <render.h>

#include <json/json.h>

#include <unistd.h>
#include <csignal>

#define MAP_SIZE_XY 22
#define SELECTED 0x90 //[targetCode code value] =  [1 001 0000]


using namespace std;
using namespace state;
using namespace render;

bool called = false;
bool readyToMove = false;

void sigalrm_handler(int sig) { 
    readyToMove = true;
    alarm(1);
}




sf::Vector2f randomPosition(sf::Vector2f currPos){
    sf::Vector2f dst = currPos;

    if(!called){
        srand (time(NULL));
    }
    int x = rand() % 2;
    if(x){
        float dx = (rand() % 3) -1;
        dst.x   += ((currPos.x + dx >=0) && (currPos.x + dx < MAP_SIZE_XY)) * dx;
    }else{
        float dy = (rand() % 3) -1;
        dst.y   += ((currPos.y + dy >=0) && (currPos.y + dy < MAP_SIZE_XY)) * dy;
    }

    return dst;
}


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



void randomMap(void){
    vector<string> mapLoc; 
    srand (time(NULL));
    int randomNb = rand() % 6;
    switch (randomNb)
    {
    case 0:
       // renderRealMap();
        break; 
    case 1:
        system("./bin/Isometric ");
        break;
    case 2:
        system("./bin/ShaderEffects");
        break;
    case 3:
        system("./bin/MapWithQuadTree");
        break;
    case 4:
        system("./bin/BenchMark");
        break;
    case 5:
        system("./bin/AddRemoveObjects");
        break;
    
    default:
      //  renderRealMap();
        break;
    }

}


 void renderMap(void){

    render::GameWindow gamewindow;
    gamewindow.update();

    sf::Event event;
    sf::Vector2i mousePosScreen = (sf::Vector2i)gamewindow.window.mapPixelToCoords(sf::Vector2i(0,0));
    gamewindow.update(event,mousePosScreen);
    float zoom = 0.8;
    int m_type = 0;

    while(gamewindow.window.isOpen()){

        mousePosScreen = (sf::Vector2i)gamewindow.window.mapPixelToCoords(sf::Mouse::getPosition(gamewindow.window));

        while(gamewindow.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                gamewindow.window.close();
            }      
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            {

            }
            if (event.type == sf::Event::MouseButtonPressed){
                switch(event.mouseButton.button)
                {
                    case sf::Mouse::Right:
                    {
                        gamewindow.setCenter((sf::Vector2f)mousePosScreen);
                        break;
                    }
                }
                gamewindow.update(event,mousePosScreen);
            }
            if(event.type == sf::Event::MouseWheelMoved)
            {
                if(event.mouseWheel.delta == 1)
                {
                    gamewindow.setZoom(0.8);
                    gamewindow.isZoomed = 1;
                }
                else
                {
                    gamewindow.setZoom(1.25);  
                    gamewindow.isZoomed = 1;
                } 
                gamewindow.update(event,mousePosScreen);          
            }
            gamewindow.update();
        }

        //gamewindow.update(event,mousePosScreen);
        gamewindow.window.clear();
        gamewindow.draw();

        gamewindow.window.display();

    }

    
} 


 void engineExplo(void){

    render::GameWindow gamewindow;
    engine::Engine ngine;
    ai::AI g_ai;
    std::unique_ptr<engine::Command> cmdHolder;
    

    gamewindow.shareStateWith(ngine);
    ngine.shareStateWith(&g_ai);
    gamewindow.update();
    //ngine.start();

    bool debug = false;
    sf::Event event;
    sf::Vector2f mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Vector2i(0,0));
    sf::Vector2f mousePosWorld  = gamewindow.screenToWorld(mousePosScreen);
    gamewindow.update(event,(sf::Vector2i)mousePosScreen);
    ngine.chrono->bind(SIGALRM);
    ngine.chrono->start(1,10);

    while(gamewindow.window.isOpen()){

        mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Mouse::getPosition(gamewindow.window));
        mousePosWorld = gamewindow.screenToWorld(mousePosScreen);
        while(gamewindow.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gamewindow.window.close();
            if(!ngine.isActionFromAI() && !ngine.timeOut()){
                gamewindow.handleEvents (event, mousePosScreen, mousePosWorld, ngine);
            }
            else if(ngine.isActionFromAI() && !ngine.timeOut()){
                g_ai.chooseAction();
                g_ai.registerActionTo(&ngine);
                ngine.execute();
            }
            else{
                ngine.execute();
            }
            
            
            gamewindow.update();
        }
        
        gamewindow.window.clear();
        gamewindow.draw();
        gamewindow.window.display();

    }

    
} 



 void random_ai(void){
    signal(SIGALRM, &sigalrm_handler); // set a signal handler 
    alarm(1);
    render::GameWindow gamewindow;
    engine::Engine ngine;
    std::unique_ptr<engine::Command> cmdHolder;
    gamewindow.shareStateWith(ngine);
    //ngine.start();

    sf::Vector2f destination = randomPosition(sf::Vector2f(11,10));
    sf::Vector2f prevPos     = destination;
    sf::Vector2f center      = destination;
    gamewindow.setCenter(gamewindow.worldToScreen(center));


    while(gamewindow.window.isOpen()){
        sf::Event event;

        while(gamewindow.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                gamewindow.window.close();
            }
            if(event.type == sf::Event::MouseWheelMoved)
            {
                if(event.mouseWheel.delta == 1)
                {
                    gamewindow.setZoom(0.8);  
                }
                else
                {
                   gamewindow.setZoom(1.25);  
                }           
            }
        }
        
        if(readyToMove){
            readyToMove = false;
            destination = randomPosition(prevPos);
            if(abs(destination.x-center.x) > 5 || abs(destination.y-center.y) > 5){
                center = destination;
                gamewindow.setCenter(gamewindow.worldToScreen(center));
            }
            cmdHolder = std::unique_ptr<engine::Command>(new engine::Command(&engine::Action::move, (int)(destination.x), (int)(destination.y)));
            ngine.execute(cmdHolder);
            prevPos     = destination;

            
        }
        gamewindow.update(event,(sf::Vector2i)destination);
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
    else if(strcmp(argv[1], "randomMap") == 0){
        randomMap();
    }else if(strcmp(argv[1], "engine") == 0){
        engineExplo();
    }else if(strcmp(argv[1], "random_ai") == 0){
        random_ai();
    }else{
        std::cout << "Expected one argument like 'client' or 'render'" << std::endl;
    }

    return 0;

}
