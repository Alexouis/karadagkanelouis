
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
/*
sf::Sprite setHeroPosition(){
    sf::Texture heroTexture;
    if (!heroTexture.loadFromFile("src/client/1.png"))
    {
        // error...
    }

    sf::Sprite heroSprite;
    heroSprite.setTexture(heroTexture);
    //heroSprite.setPosition(sf::Vector2f(20.f, 20.f));
    //heroSprite.scale(sf::Vector2f(1.f,1.f));
   // renderWindow.draw(heroSprite);
   return heroSprite;
}
*/

void renderRealMap(void){
    //create map loader and load map
        tmx::MapLoader gameMap("res/map/");
        gameMap.load("map_1.tmx");
        
        sf::RenderWindow renderWindow(sf::VideoMode(2000u, 900u), "TMX Loader");
        renderWindow.setVerticalSyncEnabled(true);

        //adjust the view to centre on map
        sf::View view = renderWindow.getView();
        view.zoom(7.0f);
        view.setCenter(1024.0f, 2000.0f);
        renderWindow.setView(view);

        sf::RenderTexture backgroundTexture;
        if (!backgroundTexture.create(5000, 5000)){}
            
        
        sf::RenderTexture playerTexture;
        if (!playerTexture.create(2000, 1000)){}
        //to toggle debug output
        bool debug = false;
        bool anim = false;
        int num_anim=0;
        //-----------------------------------//
        static float posx = 500;
        static float posy = 1500;

        sf::Vector2f move_pos(500,1500);
        sf::Vector2f move_pos_ortho;

  //      static float move_posx = 500;
  //      static float move_posy = 1500;

        Player Mustafa ;
        Mustafa.setPosition(Position());
                    
        int sens = 1;

        int i_x;
        int i_y;
        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            // error...
        }
        sf::Text text;
        text.setFont(font);
        text.setString("Hello world");
        text.setCharacterSize(250);

       // renderWindow.draw(gameMap);
        
        while(renderWindow.isOpen())
        {
            //poll input
            sf::Event event;
            playerTexture.clear();
        //	Json::Value root;
        //    Json::Reader reader;
        //    std::ifstream img("frames_info.json", );
            
            //draw map
           // renderWindow.clear();
           //playerTexture.clear(sf::Color::Red);
            
        // root["demon"]["demon_idle_w"]["n"]        
            sf::Texture heroTexture;
            if (!heroTexture.loadFromFile("res/frames.png"))
            {
                // error...
            }
   /*       sf::Sprite heroSprite;
            heroSprite.setTexture(heroTexture);
            heroSprite.setTextureRect(sf::IntRect(300,300,100,70));
            heroSprite.setPosition(sf::Vector2f(500.f, 200.f));
            heroSprite.scale(sf::Vector2f(20.f,20.f));
            sf::Sprite heroSprite2;
            heroSprite2.setTexture(heroTexture);
            heroSprite2.setTextureRect(sf::IntRect(0, 0, 100, 80));
            heroSprite2.setPosition(sf::Vector2f(-500.f, 200.f));
            heroSprite2.scale(sf::Vector2f(20.f,20.f)); */
            sf::Sprite heroSprite3;
            heroSprite3.setTexture(heroTexture);
            heroSprite3.setTextureRect(sf::IntRect(435, 520, 50, 60));
        //    heroSprite3.setPosition(sf::Vector2f(posx, posy));
            heroSprite3.setPosition(sf::Vector2f(move_pos_ortho.x-40*sens*5/2, move_pos_ortho.y-60*5)); //TESTER ANIMATION ICI
            heroSprite3.scale(sf::Vector2f(sens*5.f,5.f));
  //          backgroundTexture.draw(gameMap);
  //          playerTexture.draw(heroSprite);
  //          playerTexture.draw(heroSprite2);
  //          playerTexture.draw(heroSprite3);
  //          playerTexture.draw(text);
  //          playerTexture.display();
            renderWindow.clear();
           

            sf::Sprite bgTexture;
            bgTexture.setTexture(backgroundTexture.getTexture());
            sf::Sprite plTexture;
            plTexture.setTexture(playerTexture.getTexture());
  //          renderWindow.draw(bgTexture);           

            renderWindow.draw(gameMap);
            
            if(debug)gameMap.drawLayer(renderWindow, tmx::MapLayer::Debug);
            renderWindow.draw(heroSprite3);
//            renderWindow.draw(plTexture);
            renderWindow.display();
            //TEST POUR ANIMATION
/*            if (move_posx != posx){
                if (abs(move_posx-posx)<30) move_posx=posx;
                else if (move_posx < posx) move_posx=move_posx+30;
                else move_posx= move_posx -30;
            }
            //METTRE TOUT CA EN ORTHOGONAL
            else if (move_posy != posy){
                if (abs(move_posy-posy)<30) move_posy=posy;
                else if(move_posy < posy) move_posy=move_posy+30;
                else move_posy= move_posy -30;
            }
*/          
            sf::Vector2f destination(Mustafa.getPosition().getX()*270+270/2,Mustafa.getPosition().getY()*270+270/2);
   //       destination = gameMap.orthogonalToIsometric(posHero);
            if (move_pos.x != destination.x){
                if (abs(move_pos.x-destination.x)<30) move_pos.x=destination.x;
                else if (move_pos.x < destination.x) move_pos.x=move_pos.x+30;
                else move_pos.x= move_pos.x -30;
            }
            else if (move_pos.y != destination.y){
                 if (abs(move_pos.y-destination.y)<30) move_pos.y=destination.y;
                else if(move_pos.y < destination.y) move_pos.y=move_pos.y+30;
                else move_pos.y= move_pos.y -30;
            }

            move_pos_ortho= gameMap.isometricToOrthogonal(move_pos);


    //
    //
            //print mouse coords to orthographic (screen) coords and world (isometric) coords
            sf::Vector2f mousePosScreen = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));
            sf::Vector2f mousePosWorld = gameMap.orthogonalToIsometric(mousePosScreen);
            sf::Vector2f mousePos(floor(mousePosWorld.x/278),floor(mousePosWorld.y/278));

            std::stringstream stream;
            stream << "Mouse Position: "<< mousePosScreen.x << ", " << mousePosScreen.y << " World Position: " << mousePosWorld.x << ", " << mousePosWorld.y << " Cell: " << mousePos.x << ", " << mousePos.y;

            renderWindow.setTitle(stream.str());
            
            while(renderWindow.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    renderWindow.close();
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
                    debug = !debug;
                if(event.type == sf::Event::MouseButtonPressed){
                    //Mustafa.setPosition(Position(floor(mousePosWorld.x/278),floor(mousePosWorld.y/278)));
                    Mustafa.move(mousePos.x,mousePos.y);
                    mousePosWorld.x=mousePos.x*270+270/2;
                    mousePosWorld.y=mousePos.y*270+270/2;
                    
                    mousePosScreen = gameMap.isometricToOrthogonal(mousePosWorld);
                    i_x = Mustafa.getPosition().getX();
                    i_y = Mustafa.getPosition().getY();
                    //i_x++ ;
                    posx = mousePosScreen.x - 40*5/2;
                    posy = mousePosScreen.y - 60*5;

                    sens=-sens;

                    std::stringstream ss;
                    ss<<"Position : ("<< i_x <<","<< i_y <<")";
                    text.setString(ss.str());
                }
                
            }
        }
};





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

//ON ARRIVE PAS A CHARGER LA MAP, MAPLOADER,/// VERIFIER LOADDTEXTURE /// FAIRE MARCHER LE TOUT
 void renderMap(void){
    //tmx::MapLoader *gMap = new tmx::MapLoader("res/map/");
    //gMap->load("map_1.tmx");
    GameWindow gamewindow;
    

    while(gamewindow.window.isOpen()){
        std::cout << "11111111111\n";

        gamewindow.update();
        std::cout << "11111111111\n";

        gamewindow.window.clear();
        //gamewindow.window.draw(*gMap);
        gamewindow.draw();
        gamewindow.window.display();
      

    }

    
} 


int main(int argc,char* argv[])
{

    //GameWindow gw;


    if(argc < 2){
        std::cout << "It works ! " << std::endl;
        return 0;
    }

    if(strcmp(argv[1], "client") == 0){
        testSFML();
    }else if(strcmp(argv[1], "render") == 0){
      //  Background hahaha;
      //  Background::setGameMap(Background::getGameMap());

        renderRealMap();
    }else if(strcmp(argv[1], "renderMap") == 0){
        renderMap();
    }else if(strcmp(argv[1], "randomMap") == 0){
        randomMap();
    }
    else{
        std::cout << "Expected one argument like 'client' or 'render'" << std::endl;
    }

    return 0;

}
