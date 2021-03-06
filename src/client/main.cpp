
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
#include <ai.h>

#include <json/json.h>

#include <unistd.h>
#include <csignal>

#define MAP_SIZE_XY 22
#define SELECTED 0x90 //[targetCode code value] =  [1 001 0000]


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
                return;
            }      
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
            {
                gamewindow.update(event,mousePosScreen);
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
            if(event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonReleased)
            {
                gamewindow.update(event,mousePosScreen);
            }
            if(event.type == sf::Event::MouseWheelMoved && gamewindow.getCurrentScene() == SceneId::FIGHTSCENE)
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
    ngine.bind(&g_ai);
    gamewindow.update();
    //ngine.start();

    bool debug = false;
    sf::Event event;
    sf::Vector2f mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Vector2i(0,0));
    sf::Vector2f mousePosWorld  = gamewindow.screenToWorld(mousePosScreen);
    gamewindow.update(event,(sf::Vector2i)mousePosScreen);

    while(gamewindow.window.isOpen()){

        mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Mouse::getPosition(gamewindow.window));
        mousePosWorld = gamewindow.screenToWorld(mousePosScreen);
        while(gamewindow.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gamewindow.window.close();
                return;
            }
            else{
                gamewindow.handleZoom(event,mousePosScreen);
                if(!ngine.isActionFromAI() && !ngine.timeOut()){
                    gamewindow.handleEvents (event, mousePosScreen, mousePosWorld, ngine);
                }
                gamewindow.update();
            }
        }

        if(ngine.isActionFromAI() && !ngine.timeOut()){
            // AI
            gamewindow.update();
        }
        else if(ngine.timeOut()){
            ngine.execute();
            gamewindow.update();
        }
        
        gamewindow.window.clear();
        gamewindow.draw();
        gamewindow.window.display();

    }

    
} 




void random_ai(void){
    render::GameWindow gamewindow;
    engine::Engine ngine;
    ai::AI g_ai;
    std::unique_ptr<engine::Command> cmdHolder;
    ai::AI::initSrand();

    gamewindow.shareStateWith(ngine);
    ngine.bind(&g_ai);
    gamewindow.update();
    //ngine.start();

    bool debug = false;
    sf::Event event;
    sf::Vector2f mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Vector2i(0,0));
    sf::Vector2f mousePosWorld  = gamewindow.screenToWorld(mousePosScreen);
    gamewindow.update(event,(sf::Vector2i)mousePosScreen);

    while(gamewindow.window.isOpen()){

        mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Mouse::getPosition(gamewindow.window));
        mousePosWorld = gamewindow.screenToWorld(mousePosScreen);
        while(gamewindow.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gamewindow.window.close();
                return;
            }
            else{
                gamewindow.handleZoom(event,mousePosScreen);
                if(!ngine.isActionFromAI() && !ngine.timeOut()){
                    gamewindow.handleEvents (event, mousePosScreen, mousePosWorld, ngine);
                }
                gamewindow.update();
            }
        }

        if(ngine.isActionFromAI() && !ngine.timeOut()){
            g_ai.exploit();
            ngine.execute();
        }
        else if(ngine.timeOut()){
            ngine.execute();
        }
        
        gamewindow.update();
        gamewindow.window.clear();
        gamewindow.draw();
        gamewindow.window.display();

    }
    
} 



void heuristic_ai(void){
    render::GameWindow gamewindow;
    engine::Engine ngine;
    ai::HeuristicAI g_ai;
    std::unique_ptr<engine::Command> cmdHolder;
    ai::AI::initSrand();

    gamewindow.shareStateWith(ngine);
    ngine.bind(&g_ai);
    gamewindow.update();
    //ngine.start();

    bool debug = false, timeOut;
    sf::Event event;
    sf::Vector2f mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Vector2i(0,0));
    sf::Vector2f mousePosWorld  = gamewindow.screenToWorld(mousePosScreen);
    gamewindow.update(event,(sf::Vector2i)mousePosScreen);

    while(gamewindow.window.isOpen()){

        mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Mouse::getPosition(gamewindow.window));
        mousePosWorld = gamewindow.screenToWorld(mousePosScreen);
        
        while(gamewindow.window.pollEvent(event)) {
            timeOut = ngine.timeOut();
            if (event.type == sf::Event::Closed) {
                gamewindow.window.close();
                return;
            }
            else{
                gamewindow.handleZoom(event,mousePosScreen);
                if(!ngine.isActionFromAI() && !timeOut){
                    gamewindow.handleEvents (event, mousePosScreen, mousePosWorld, ngine);  
                    gamewindow.update(); 
                }

            }
        }

        if(ngine.isActionFromAI() && !ngine.timeOut()){
            g_ai.exploit();
            gamewindow.update();
        }
        else if(ngine.timeOut()){
            gamewindow.update();
        }
        
        gamewindow.update();
        gamewindow.window.clear();
        gamewindow.draw();
        gamewindow.window.display();

    }
    
} 



void rollback(void){
    render::GameWindow gamewindow;
    engine::Engine ngine;
    ai::HeuristicAI g_ai;
    std::unique_ptr<engine::Command> cmdHolder;
    ai::AI::initSrand();

    gamewindow.shareStateWith(ngine);
    ngine.bind(&g_ai);
    gamewindow.update();
    //ngine.start();

    bool debug = false, timeOut;
    sf::Event event;
    sf::Vector2f mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Vector2i(0,0));
    sf::Vector2f mousePosWorld  = gamewindow.screenToWorld(mousePosScreen);
    gamewindow.update(event,(sf::Vector2i)mousePosScreen);

    while(gamewindow.window.isOpen()){

        mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Mouse::getPosition(gamewindow.window));
        mousePosWorld = gamewindow.screenToWorld(mousePosScreen);
        
        while(gamewindow.window.pollEvent(event)) {
            timeOut = ngine.timeOut();
            if (event.type == sf::Event::Closed) {
                gamewindow.window.close();
                return;
            }
            else{
                gamewindow.handleZoom(event,mousePosScreen);
                if(!ngine.isActionFromAI() && !timeOut){
                    gamewindow.handleEvents (event, mousePosScreen, mousePosWorld, ngine);  
                    gamewindow.update(); 
                }

            }
        }

        if(ngine.isActionFromAI() && !ngine.timeOut()){
            g_ai.exploit();
            gamewindow.update();
        }
        else if(ngine.timeOut()){
            gamewindow.update();
        }
        
        gamewindow.update();
        gamewindow.window.clear();
        gamewindow.draw();
        gamewindow.window.display();

    }
    
} 




void deep_Ai(void){
    render::GameWindow gamewindow;
    engine::Engine ngine;
    std::unique_ptr<engine::Command> cmdHolder;
    ai::AI::initSrand();

    gamewindow.shareStateWith(ngine);
    ai::DeepAI g_ai(&ngine);
    gamewindow.update();
    //ngine.start();

    bool debug = false, timeOut;
    sf::Event event;
    sf::Vector2f mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Vector2i(0,0));
    sf::Vector2f mousePosWorld  = gamewindow.screenToWorld(mousePosScreen);
    gamewindow.update(event,(sf::Vector2i)mousePosScreen);

    while(gamewindow.window.isOpen()){

        mousePosScreen = gamewindow.window.mapPixelToCoords(sf::Mouse::getPosition(gamewindow.window));
        mousePosWorld = gamewindow.screenToWorld(mousePosScreen);
        
        while(gamewindow.window.pollEvent(event)) {
            timeOut = ngine.timeOut();
            if (event.type == sf::Event::Closed) {
                gamewindow.window.close();
                return;
            }
            else{
                gamewindow.handleZoom(event,mousePosScreen);
                if(!ngine.isActionFromAI() && !timeOut){
                    gamewindow.handleEvents (event, mousePosScreen, mousePosWorld, ngine);  
                    gamewindow.update(); 
                }

            }
        }

        if(ngine.isActionFromAI() && !ngine.timeOut()){
            g_ai.exploit();
            gamewindow.update();
        }
        else if(ngine.timeOut()){
            gamewindow.update();
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
    else if(strcmp(argv[1], "randomMap") == 0){
        randomMap();
    }else if(strcmp(argv[1], "engine") == 0){
        engineExplo();
    }else if(strcmp(argv[1], "random_ai") == 0){
        random_ai();
    }else if(strcmp(argv[1], "heuristic_ai") == 0){
        heuristic_ai();
    }else if(strcmp(argv[1], "deep_ai") == 0){
        deep_Ai();
    }else{
        std::cout << "Expected one argument like 'client' or 'render'" << std::endl;
    }

    return 0;

}
