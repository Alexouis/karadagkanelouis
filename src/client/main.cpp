
#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>

#include "jsoncpp/json/json.h"
#include <iostream>
#include <fstream>
#include <math.h>

#include <tmx/MapLoader.hpp>
#include <sstream>
#include <string>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


// Fin test SFML
#include <thread>
#include  <state.h>
#include <json/json.h>

using namespace std;
using namespace state;


void clientTest(void){
    Exemple exemple;
    exemple.setX(53);
    //MapLoader::MapLoader("res/map");
    cout << "It works !" << endl;
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



void renderRealMap(void){
    
    
    //create map loader and load map
	tmx::MapLoader ml("res/map/");
	ml.load("map_1.tmx");
	
	sf::RenderWindow renderWindow(sf::VideoMode(2000u, 600u), "TMX Loader");
	renderWindow.setVerticalSyncEnabled(true);

	//adjust the view to centre on map
	sf::View view = renderWindow.getView();
	view.zoom(7.0f);
	view.setCenter(1024.0f, 2000.0f);
	renderWindow.setView(view);


	//to toggle debug output
	bool debug = false;
    bool anim = false;
    int num_anim=0;
	//-----------------------------------//
    static int posHero = 1;
    static float posx = 500;
    static float posy = 1500;

    Player Mustafa ;
    Mustafa.setPosition(Position());
                
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

	while(renderWindow.isOpen())
	{
		//poll input
		sf::Event event;
        
	//	Json::Value root;
    //    Json::Reader reader;
    //    std::ifstream img("frames_info.json", );

        
		//draw map
		renderWindow.clear();
		
       // root["demon"]["demon_idle_w"]["n"]        
        sf::Texture heroTexture;
        if (!heroTexture.loadFromFile("res/frames.png"))
        {
            // error...
        }
        sf::Sprite heroSprite;
        heroSprite.setTexture(heroTexture);
        heroSprite.setTextureRect(sf::IntRect(300,300,100,70));
        heroSprite.setPosition(sf::Vector2f(500.f, 200.f));
        heroSprite.scale(sf::Vector2f(20.f,20.f));
        sf::Sprite heroSprite2;
        heroSprite2.setTexture(heroTexture);
        heroSprite2.setTextureRect(sf::IntRect(0, 0, 100, 80));
        heroSprite2.setPosition(sf::Vector2f(-500.f, 200.f));
        heroSprite2.scale(sf::Vector2f(20.f,20.f));
        sf::Sprite heroSprite3;
        heroSprite3.setTexture(heroTexture);
        heroSprite3.setTextureRect(sf::IntRect(435, 520, 50, 60));
        heroSprite3.setPosition(sf::Vector2f(posHero*posx, posy));
        heroSprite3.scale(sf::Vector2f(20.f,20.f));
        renderWindow.draw(ml);
        renderWindow.draw(heroSprite);
        renderWindow.draw(heroSprite2);
        renderWindow.draw(heroSprite3);
        renderWindow.draw(text);
		if(debug)ml.drawLayer(renderWindow, tmx::MapLayer::Debug);
		renderWindow.display();


		//print mouse coords to orthographic (screen) coords and world (isometric) coords
		sf::Vector2f mousePosScreen = renderWindow.mapPixelToCoords(sf::Mouse::getPosition(renderWindow));
		sf::Vector2f mousePosWorld = ml.orthogonalToIsometric(mousePosScreen);

		std::stringstream stream;
		stream << "Mouse Position: "<< mousePosScreen.x << ", " << mousePosScreen.y << " World Position: " << mousePosWorld.x << ", " << mousePosWorld.y;

		renderWindow.setTitle(stream.str());
		
        while(renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
				debug = !debug;
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
				if(posHero==1) posHero= -1;
                else posHero =1;
            if(event.type == sf::Event::MouseButtonPressed){
                //Mustafa.setPosition(Position(floor(mousePosWorld.x/278),floor(mousePosWorld.y/278)));
                Mustafa.move(floor(mousePosWorld.x/278),floor(mousePosWorld.y/278));
                mousePosWorld.x=floor(mousePosWorld.x/278)*270+270/2;
                mousePosWorld.y=floor(mousePosWorld.y/278)*270+270/2;
                
                mousePosScreen = ml.isometricToOrthogonal(mousePosWorld);
                i_x = Mustafa.getPosition().getX();
                i_y = Mustafa.getPosition().getY();
                //i_x++ ;
				posx = mousePosScreen.x - 40*20/2;
                posy = mousePosScreen.y - 60*20;

                std::stringstream ss;
                ss<<"Position : ("<< i_x <<","<< i_y <<")";
                text.setString(ss.str());
            }
            
        }
	}
}




void randomMap(void){
    vector<string> mapLoc; 
    srand (time(NULL));
    int randomNb = rand() % 6;
    switch (randomNb)
    {
    case 0:
        renderRealMap();
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
        renderRealMap();
        break;
    }

}





int main(int argc,char* argv[])
{
    if(argc < 2){
        std::cout << "It works ! " << std::endl;
        return 0;
    }

    if(strcmp(argv[1], "client") == 0){
        testSFML();
    }else if(strcmp(argv[1], "render") == 0){
        renderRealMap();
    }else if(strcmp(argv[1], "randomMap") == 0){
        randomMap();
    }
    else{
        std::cout << "Expected one argument like 'client' or 'render'" << std::endl;
    }

    return 0;

}
